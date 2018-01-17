void f(int *a)
{
    *a = 12;
}

int main(void)
{
    int a;
    f(&a);
    printf("%d\n", a);
}