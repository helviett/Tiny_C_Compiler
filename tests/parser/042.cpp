int main(void)
{
    int a = 10;
    label1:
    a += 10;
    label2:
    {
        a -= 12;
        goto label1;
    }
}