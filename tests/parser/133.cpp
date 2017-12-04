int main(void)
{
    struct {int a;} *a;
    &(a + 2)->a;
}