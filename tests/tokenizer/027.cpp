void lc(char *str)
{
    for(int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] += 32;
    }
}