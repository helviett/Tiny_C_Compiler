struct A
{
    float a;
    int b;
    struct A c;
};

int main(void)
{
    struct A a1;
    a1.a = 3;
    printf("%f\n", a1.a);
}