struct {int a;} *f(void) {}

int main(void)
{
    f()->a = 12;
}

