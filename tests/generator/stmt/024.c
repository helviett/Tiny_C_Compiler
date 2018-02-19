typedef struct A
{
    int a;
    int b[2][2];
} A;

int cmp(A *a1, A *a2)
{
    return  a1->a == a2->a && a1->b[0][0] == a2->b[0][0] && a1->b[0][1] == a2->b[0][1] && a1->b[1][0] == a2->b[1][0]
            && a1->b[1][1] == a2->b[1][1];
}

int main(void)
{
    A a, b;
    a.a = 3;
    a.b[0][0] = 0;
    a.b[0][1] = 1;
    a.b[1][0] = 10;
    a.b[1][1] = 11;
    b = a;
    printf("%d\n", cmp(&a, &b));
    return 0;
}