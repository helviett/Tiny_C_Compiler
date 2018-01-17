struct A
{
    float a;
    int b;
};

int main(void)
{
    struct A a;
    struct A *pa;
    pa = &a;
    a.b = 12;
    printf("%d\n", pa->b);
    return 0;
}