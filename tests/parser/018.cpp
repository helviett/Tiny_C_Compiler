int main(void)
{
    int a, b, longername, *pointer;
    -a;
    +b;
    &longername;
    *pointer;
    !0;
    ~1;
    ++a;
    --b;
    ++--longername;
    sizeof 10;
    sizeof -10;
    sizeof ++10;
    sizeof --(-10);
    sizeof(int);
    sizeof(int **);
    sizeof(int * const);
    return 0;
}