typedef struct A
{
    int a;
    int b;
} A;

int main(void)
{
    A a, b;
    a.a = 1;
    a.b = 2;
    b = a;
    printf("%d %d\n", b.a, b.b);
    return 0;
}