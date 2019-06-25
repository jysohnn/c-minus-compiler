/* calculate fibonacci number */
int sol;

int fibonacci(int x)
{
  if(x <= 0) return 0;
  else if(x == 1) return 1;
  else if(x == 2) return 1;
  else return fibonacci(x-1) + fibonacci(x-2);
}

void main(void)
{
  int x;
  x = input();
  sol = fibonacci(x);
  output(sol);
}
