int main(void)
{
    struct A {int a;} a;
    a.a.a = 10;
    return 0;
}