// Compute sum of consecutive integers from 1 to N (inclusive)
long cumulative_sum(int N) {
//      long accumulator;
//      if (N==1) {
//              accumulator = 1;
//      } else {
//              accumulator = N + cumulative_sum(N-1);
//      }
//
//        return accumulator;
        long accumulator = 0;
        for (int i=1; i<=N; i++) {
                accumulator += i;
        }

        return accumulator;
}

