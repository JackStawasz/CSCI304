#include <limits.h>
#include <pthread.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#define TIME(x) time_t (x) = time(NULL)

typedef unsigned long ulong;

const int CKPT_HZ = 100000000;

/* cilk2c will build a _cilk_*_snapshot for each task. */
struct _cilk_sum_snapshot {
	int i, *ip;
	long sum, *sump;
};

/*
 * Do we need another "program counter"? Each task frame already has an entry
 * member that is designed to dispatch control to the proper entry point in the
 * the slow clone after the corresponding task is robbed. Using this value in
 * the task frame's header member seems to simplify recovery, but we should
 * improve the resolution of recovery beyond Cilk-thread granularity.
 * Essentially, this will be the variable that is passed to longjmp, so the
 * handler can rollback the program to the latest consistent state. NOTE: We
 * may need to consider synchronization primitives to adjudicate access to this
 * datum.
 */ 
int _cilk_sum_recovery_entry = 0;

/*
 * We're using the setjmp API to handle asynchronous elbows to our running
 * tasks. cilk2c will define a _cilk_*_buf object for each task.
 */
jmp_buf _cilk_sum_buf;

/*
 * Are there types that we are already using that we can augment to track
 * global objects like _cilk_sum_recovery_entry and _cilk_sum_buf?
 */

/*
 * A repository is a collection of snapshots. NOTE: cilk-repo.[c,h] and
 * cilk-resilience.[c,h] contain other notes on a repo module. We can store the
 * repo in context->Cilk_global_state->repository on the heap.
 */
struct _cilk_sum_snapshot repository[2] = { { 0, NULL, 0, NULL }, { 0, NULL, 0, NULL } };

/* Compute the sum of natural numbers from 0 to INT_MAX - 1. */
void serial_benchmark(void);

/* Compute the sum of natural numbers from 0 to INT_MAX - 1. */
void *sum(void *args);

/* Handle asynchronous elbows. */
void recovery_handler(int sig);

/* Rollback to a consistent program state. */
void _cilk_sum_rollback(struct _cilk_sum_snapshot *snapshot);

/* Save the program state. */
void _cilk_sum_checkpoint(struct _cilk_sum_snapshot *snapshot);

/* Main simulates the Cilk runtime system. */
int main(void)
{
	printf("Running the serial benchmark...");
	serial_benchmark();

	/* Register the recovery handler. */
	signal(SIGUSR1, recovery_handler);

	pthread_t thread0, thread1;
	pthread_create(&thread0, NULL, &sum, (void *) &repository[0]);
	pthread_create(&thread1, NULL, &sum, (void *) &repository[1]);

	/* Get some work done before signaling a thread. */
	sleep(3);

	/* Signal one of the two threads to simulate hardware interrupt. */
	pthread_kill(thread0, SIGUSR1);

	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);

	return 0;
}

void serial_benchmark(void)
{
	int i;
	long sum = 0;

	TIME(tic);
	for (i = 0; i < INT_MAX; i++) sum += i;
	TIME(toc);

	printf("time = %lu seconds::sum = %ld\n", (ulong) (toc - tic), sum);
}

void *sum(void *args)
{
	printf("Create THREAD ID %#010x...\n", (ulong) pthread_self());

	int i;
	long sum = 0;

	struct _cilk_sum_snapshot *snapshot = (struct _cilk_sum_snapshot *) args;
	snapshot->ip = &i;
	snapshot->sump = &sum;

	if (setjmp(_cilk_sum_buf)) {
		_cilk_sum_rollback(snapshot);
		switch(_cilk_sum_recovery_entry) {
			case 1:
				printf("Dispatch control to entry %d...\n", _cilk_sum_recovery_entry);
				goto entry1;
		}
	}

	TIME(tic);
	for (i = 0; i < INT_MAX; i++) {
		/* KLUDGE */
		//if (i % CKPT_HZ == 0) { /* Checkpoint once every CKPT_HZ iterations. */
		if (i == 1000000) { /* Checkpoint once. */ 
			_cilk_sum_checkpoint(snapshot);
			_cilk_sum_recovery_entry = 1;
		}
		entry1: sum += i;
	}
	TIME(toc);

	printf("THREAD ID %#010x::time = %lu seconds::sum = %ld\n",
		(ulong) pthread_self(), (ulong) (toc - tic), sum);
}

void recovery_handler(int sig)
{
	/* printf is not safe, but this just serves as a diagnostic. */ 
	printf("Signal THREAD ID %#010x...\n", (ulong) pthread_self());
	longjmp(_cilk_sum_buf, _cilk_sum_recovery_entry);
}

void _cilk_sum_rollback(struct _cilk_sum_snapshot *snapshot)
{
	*snapshot->ip = snapshot->i;
	*snapshot->sump = snapshot->sum;
}

/* Plank et al. use system calls to implement incremental checkpointing. */ 
void _cilk_sum_checkpoint(struct _cilk_sum_snapshot *snapshot)
{
	snapshot->i = *snapshot->ip;
	snapshot->sum = *snapshot->sump;
}
