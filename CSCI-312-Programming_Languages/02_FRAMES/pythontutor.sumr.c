main()
{
  int n = 3;
  printf("The sum from 1 to %d is %d\n", n, csum(n));
}

int csum(int n)
{
  int cumulative_sum, accumulator;
 
  if (n < 2) {
    cumulative_sum = 1;
    return cumulative_sum;
  } else {
    cumulative_sum = csum(n-1);
    accumulator = n + cumulative_sum;
    return accumulator;
  }
}
