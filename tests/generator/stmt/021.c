struct A
{
    float a;
    int b;
};

int main(void)
{
    struct A as[10];
    int i = 0;
    for (; i < 10; ++i)
    {

        as[i].a = i * 2;
        as[i].b = i * i;
    }
    for (i = 0; i < 10; ++i)
    {
        printf("(%f, %d)\t", as[i].a, as[i].b);
    }
    printf("\n");
    return 0;
}