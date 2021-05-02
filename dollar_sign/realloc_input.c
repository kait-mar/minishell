#include "../minishell.h"

char    *realloc_input(char *str, char *s, int len, int string_len, int i)
{
    int o;
    int len_before;
    int len_after;
    int len_cmd;
    int j;
    char *string;

    len_after = 0;
    len_before = 0;
    len_cmd = ft_strlen(s);
    o = 0;
    j = 0;
    while (o < i && str[o] != '\0')
    {
        len_before += 1;
        o += 1;
    }
    o += (len );
    while (str[o] != '\0')
    {
        len_after += 1;
        o += 1;
    }
    if (!(string = (char *) ft_calloc(sizeof (char), (len_cmd + len_after + len_before) + 1)))
        return (NULL);
    i = 0;
    while (len_before > 0)
    {
        string[i] = str[i];
        i += 1;
        len_before--;
    }
    while (len_cmd >= 0 && s[j] != '\0')
    {
        string[i] = s[j];
        i += 1;
        j += 1;
        len_cmd--;
    }
    len_before  = string_len;
    while (len_after > 0)
    {
        string[i] = str[len_before];
        len_after--;
        i += 1;
        len_before += 1;
    }
    string[i] = '\0';
    free(str);
    return (string);
}

/*t_sign  realloc_input(char *str, int string_len, t_sign lst)
{
    int o;
    int len_before;
    int len_after;
    int len_cmd;
    int j;

    len_after = 0;
    len_before = 0;
    len_cmd = ft_strlen(lst.s);
    o = 0;
    j = 0;
    while (o < lst.i && str[o] != '\0')
    {
        len_before += 1;
        o += 1;
    }
    o += (lst.j);
    while (str[o] != '\0')
    {
        len_after += 1;
        o += 1;
    }
    lst.string = (char *) ft_calloc(sizeof (char), (len_cmd + len_after + len_before) + 1);
    if (lst.string == NULL)
    {
        lst.error = -1;
        return (lst);
    }
    lst.i = 0;
    while (len_before > 0)
    {
        lst.string[lst.i] = str[lst.i];
        lst.i += 1;
        len_before--;
    }
    while (len_cmd >= 0 && lst.s[j] != '\0')
    {
        lst.string[lst.i] = lst.s[j];
        lst.i += 1;
        j += 1;
        len_cmd--;
    }
    len_before  = string_len;
    while (len_after > 0)
    {
        lst.string[lst.i] = str[len_before];
        len_after--;
        lst.i += 1;
        len_before += 1;
    }
    lst.string[lst.i] = '\0';
    free(str);
    return (lst);
}*/