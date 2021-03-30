#include "minishell.h"

int     check_escape_meta(char *str, int i)
{
    while (str[i] == '\\')
        i += 1;
    if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
        return (1);
    return (0);
}

int     check_escape_dollar(char *str, int i)
{
    while (str[i] == '\\')
        i += 1;
    if (str[i] == '$')
        return (1);
    return (0);
}

int     count_escape(char *str, int i)
{
    int count;

    count = 0;
    while (str[i] == '\\')
    {
        i += 1;
        count += 1;
    }
    return (count);
}

int     new_space(char *str)
{
    int i;
    int escape_nmbr;
    int count;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            if (check_escape_meta(str, i) == 1)
            {
                while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != ';')
                {
                    i += 1;
                    count += 1;
                }
                if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';')
                {
                    i += 1;
                    count += 1;
                }
            }
            else if (check_escape_dollar(str, i) == 1)
            {
                while (str[i] != '$')
                {
                    i += 1;
                    count += 1;
                }
                if (str[i] == '$')
                {
                    i++;
                    count++;
                }
            }
            else
            {
                escape_nmbr = count_escape(str, i);
                escape_nmbr = escape_nmbr % 2;
                while (str[i] == '\\')
                    i += 1;
                count += escape_nmbr;
                if (str[i] != '\\')
                    i++;
                count++;
            }
        }
        else
        {
            i += 1;
            count += 1;
        }
    }
    return (count);
}

char    *escape_normal(char *str)
{
    int i;
    int j;
    char *string;

    i = 0;
    j = 0;
    if (!(string = (char *) ft_calloc(sizeof(char) , (new_space(str) + 1))))
        return (NULL);
    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            if (check_escape_meta(str, i) == 1)
            {
                while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != ';')
                {
                    string[j] = str[i];
                    j += 1;
                    i += 1;
                }
                if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';')
                {
                    string[j] = str[i];
                    i += 1;
                    j += 1;
                }
            }
            else if (check_escape_dollar(str, i) == 1)
            {
                while (str[i] != '$')
                {
                    string[j] = str[i];
                    j += 1;
                    i += 1;
                }
                if (str[i] == '$')
                {
                    string[j] = str[i];
                    j += 1;
                    i += 1;
                }
                if (str[i] == '\\')
                {
                    while (str[i] == '\\')
                        string[j++] = str[i++];
                }
            }
            else if (check_escape_space(str, i) == 1)
            {
                while (str[i] != ' ')
                {
                    string[j] = str[i];
                    j += 1;
                    i += 1;
                }
                if (str[i] == ' ')
                {
                    string[j] = str[i];
                    j += 1;
                    i += 1;
                }
            }
            else
            {
                i += 1;
                string[j] = str[i];
                j += 1;
                i += 1;
            }
        }
        else if (str[i] == '$' && str[i + 1] == '\\')
        {
            string[j++] = str[i++];
            while (str[i] == '\\')
                string[j++] = str[i++];
        }
        else
        {
            string[j] = str[i];
            i += 1;
            j += 1;
        }
    }
    string[j] = '\0';
    return (string);
}

int     active(char *str, int i)
{
    int count;

    count = 0;
    if (str[i - 1] == '\\')
    {
        i -= 1;
        while (str[i] == '\\')
        {
            i -= 1;
            count += 1;
        }
        if ((count % 2) == 0)
            return (1);
        else
            return (0);
    }
    return (1);
}

int     count_meta_space(char *str)
{
    int i;
    int nbr;
    int count;

    i = 0;
    count = 0;
    nbr = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            if (check_escape_meta(str, i) == 1)
            {
                while (str[i] == '\\')
                {
                    i += 1;
                    nbr += 1;
                }
                count += nbr % 2;
                if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';')
                    i += 1;
            }
            else
            {
                i += 1;
                count += 1;
            }
        }
        else
        {
            i += 1;
            count += 1;
        }
    }
    return (count);
}

char    *escape_meta(char *str)
{
    int i;
    int j;
    char *string;

    i = 0;
    j = 0;
    if (!(string = (char *) ft_calloc(sizeof (char) , (count_meta_space(str) + 1))))
        return (NULL);
    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            if (check_escape_meta(str, i) == 1 || check_escape_space(str, i) == 1)
            {
                while ((str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != ';'
                    && str[i] != '\0' && str[i] != ' ') && str[i] == '\\')
                {
                    i += 1;
                    string[j] = str[i];
                    i += 1;
                    j += 1;
                }
            }
            else
            {
                string[j] = str[i];
                j += 1;
                i += 1;
            }
        }
        else
        {
            string[j] = str[i];
            j += 1;
            i += 1;
        }
    }
    string[j] = '\0';
    return (string);
}

int     count_dollar_escape(char *s)
{
    int i;
    int nb_escape;
    int count;

    i = 0;
    count = 0;
    nb_escape = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\\' && check_escape_dollar(s, i) == 1)
        {
            while (s[i] == '\\')
            {
                i += 1;
                nb_escape += 1;
            }
            if (s[i] == '$')
            {
                i += 1;
                count += 1;
            }
            count += nb_escape % 2;
        }
        else
        {
            i += 1;
            count += 1;
        }
    }
    return (count);
}

char    *remove_escape_dollar(char *s)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    if(!(str = (char *) malloc((sizeof (char) * count_dollar_escape(s)))))
        return (NULL);
    while (s[i] != '\0')
    {
        if (s[i] == '\\' && check_escape_dollar(s, i) == 1)
        {
            while (s[i] == '\\')
            {
                i += 1;
                str[j] = s[i];
                j += 1;
                i += 1;
            }
            str[j++] = s[i++];
        }
        else if (s[i] == '$' && s[i + 1] == '\\')
        {
            str[j++] = s[i++];
            while (s[i] == '\\')
            {
                i += 1;
                str[j] = s[i];
                j += 1;
                i += 1;
            }
            str[j++] = s[i++];
        }
        else
            str[j++] = s[i++];
    }
    str[j] = '\0';
    return (str);
}