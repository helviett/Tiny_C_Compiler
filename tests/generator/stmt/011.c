int main(void)
{
    int a = 12;
    int *pa = &a;
    int **ppa = &pa;
    printf("%d\n", **ppa == pa[0]);
    return 0;
}