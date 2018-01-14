int main(void)
{
    int a = 0;
    int b = 2;
    if (a + b < 0)
        a--;
    if (a * b >= 0)
        ++b;
    printf("%d %d\n", a, b);
}
