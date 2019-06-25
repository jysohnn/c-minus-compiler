/* calculate gcd(a, b) */
int gcd(int x, int y)
{
    if(y == 0) return x;
    return gcd(y, x - (x / y) * y);
}

void main(void)
{
    int a;
    int b;
    a = input();
    b = input();
    output(gcd(a, b));
}