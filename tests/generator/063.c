
int main(void)
{
    int a = 12;
    int *pa = &a;
    *pa = 13;
    printf("%d\n", a);
    return 0;
}