#include "minishell.h"

int     check_escape_space(char *string, int i)
{
    while (string[i] != '\0')
    {
        if (string[i] == '\\')
        {
            while (string[i] == '\\')
                i++;
            if (string[i] == ' ')
                return (1);
        }
        i += 1;
    }
    return (0);
}

int     count_new(char *str)
{
    int i;
    int j;
    int start;
    int end;
    int count;
    int on;

    i = 0;
    count = 0;
    end = 0;
    start = 0;
    on = 0;
    while (str[i] == ' ')
        i += 1;
    start = i;
    count = start;
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
            on = 1;
        if (str[i + 1] == '\0' && str[i] == ' ' && on == 1)
        {
            j = i;
            while (str[j] == ' ')
            {
                j -= 1;
                end += 1;
            }
            if (str[j] == '\\')
                end -= 1;
        }
        i += 1;
        count  += 1;
    }
    count -= (start + end);
    return (count);
}


char    *remove_space(char *string)
{
    int i;
    int j;
    int start;
    int end;
    char *str;

    i = 0;
    j = 0;
    if (!(str = (char *) malloc(sizeof (char ) * (count_new(string) + 1))))
        return (NULL);
    while (string[i] == ' ')
        i += 1;
    start = i;
    end = ft_strlen(string) - 1;
    while (string[end] == ' ')
        end--;
    if (string[end] == '\\')
        end += 1;
    while (start <= end)
    {
        if (string[start] == '"')
        {
            str[j++] = string[start++];
            while (string[start] != '\0' && string[start] != '"')
            {
                str[j] = string[start];
                j += 1;
                start += 1;
            }
            str[j++] = string[start++];
        }
        else if (string[start] == '\'')
        {
            str[j++] = string[start++];
            while (string[start] != '\0' && string[start] != '\'')
            {
                str[j] = string[start];
                j += 1;
                start += 1;
            }
            str[j++] = string[start++];
        }
        else if (string[start] == ' ' && active(string, start) == 1)
        {
            str[j++] = string[start++];
            while (string[start] == ' ')
                start++;
        }
        else if (string[start] == ' ' && active(string,start) == 0)
            str[j++] = string[start++];
        else
        {
            str[j] = string[start];
            j += 1;
            start += 1;
        }
    }
    str[j] = '\0';
    return (str);
}