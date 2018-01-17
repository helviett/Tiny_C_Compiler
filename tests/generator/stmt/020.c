struct A
{
    float a;
    int b;
    struct A *c;
};

int main(void)
{
    struct A a1;
    struct A a2;
    a2.b = 3;
    a1.c = &a2;
    printf("%d\n", (*a1.c).b == a1.c->b);
}