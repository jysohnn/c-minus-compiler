int a[100];

void fa(int x, int y[])
{
    output(y[x]);
}

void fb(int arr[], int idx)
{
    output(arr[idx]);
    arr[9] = 3;
    fa(9, arr);
}

void fc(int brr[], int idx)
{
    output(brr[idx]);
    a[4] = 2;
    fb(a, 4);
}

void main(void)
{
    int b[100];
    b[8] = 1;
    fc(b, 8);
}