typedef struct B
{
    float a[2];
    int b;
} B;

typedef struct A
{
    int a;
    int b[2][2];
    B c;
} A;

//int cmp(A *a1, A *a2)
//{
//    return  a1->a == a2->a && a1->b[0][0] == a2->b[0][0] && a1->b[0][1] == a2->b[0][1] && a1->b[1][0] == a2->b[1][0]
//            && a1->b[1][1] == a2->b[1][1]
//            && a1->c.a[0] == a2->c.a[0] && a1->c.a[1] == a2->c.a[1] && a1->c.b == a2->c.b;
//}

int main(void)
{
    A a, b;
//    a.a = 3;
//    a.b[0][0] = 0;
//    a.b[0][1] = 1;
//    a.b[1][0] = 10;
//    a.b[1][1] = 11;
//    a.c.a[0] = 2.7;
//    a.c.a[1] = 3.14;
    a.c.b = 123;
    b = a;
    printf("%d\n", b.c.b);
//    printf("%d %d %d %d %d %f %f %d", a.a, a.b[0][0], a.b[0][1], a.b[1][0], a.b[1][1], a.c.a[0], a.c.a[1], a.c.b);
//    printf("%d\n", cmp(&a, &b));
    return 0;
}