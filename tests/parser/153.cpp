int main(void)
{
    struct A {const int a;} *a;
    a->a = 3;
}