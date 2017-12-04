int main(void)
{
    struct A {int a;} *a;
    float c = a->a == 123 ? 1 : 2;
}