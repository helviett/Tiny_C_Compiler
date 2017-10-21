void error(struct Err *e)
{
    printf("Error %s: Code %d", e->msg, e->code);
}