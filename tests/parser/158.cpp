// let's assume that function definition (at least main) works good
int main(void)
{
    struct A {int a;} a;
    int b;
    (struct A *) b;
    return 0;
}