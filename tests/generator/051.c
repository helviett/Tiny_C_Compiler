
int main(void)
{
    int a[3];
    int *begin = a;
    int *end = a + 2;
    printf("%d\n", (end - begin));
}
