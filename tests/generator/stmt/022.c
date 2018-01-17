struct A
{
    float a;
    int b;
};

void printArray(struct A a[], int n)
{
    int i = 0;
    for (; i < 10; ++i)
    {
        printf("(%f, %d)\t", a[i].a, a[i].b);
    }
    printf("\n");
}

int main(void)
{
    struct A as[10];
    int i = 0;
    for (; i < 10; ++i)
    {
        as[i].a = i * 2;
        as[i].b = i * i;
    }
    printArray(as, 10);
    return 0;
}