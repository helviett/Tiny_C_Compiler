typedef int A;
typedef double *B[10];
typedef char* (*(*C[5])(int))[];

int main(void)
{
    A a;
    B b;
    C c;
    *(*(*c[0])(a))[0];
}