
#include "minishell.h"

/*
int	print_env_two(char *bult, char **env, int which_quote, char **string)
{
    char	**str;
    int		j;
    char	**tab;
    int		i;
    int count;

    i = 0;
    count = 0;
    while (*bult)
    {
        if (*bult == '\\' && *(bult + 1) == '\\')
        {
            j = how_many_escape(bult);
            if (j % 2 != 0)
            {
                while (*(bult + 1) == '\\')
                    (bult)++;
            }
            else
            {
                while (*bult == '\\')
                    (bult)++;
            }
            j /= 2;
            while (--j >= 0)
                count++;
        }
        if (*bult == '\\' && (*(bult + 1) == '$' || *(bult + 1) == '"' || *(bult + 1) == '\''))
        {
            //ft_printf("here\n");
            bult += 2;
            count++;
        }
        while (*bult != '$' && *bult != '\0' && (*bult != '\\' || *(bult + 1) != '\\') && (*bult != '\\' || *(bult + 1) != '$') && (*bult != '\\' || *(bult + 1) != '\'') && (*bult != '\\' || *(bult + 1) != '"'))
        {
            bult++;
            count++;
        }
        if (*bult == '\\' && (*(bult + 1) == '\\' || *(bult + 1) == '$'))
            continue ;
        if ((*bult == '$' && ((which_quote == 0 && (*(bult + 1) == '\0' || *(bult + 1) == ' ')) || (which_quote == 1 && (*(bult  + 1) == 39 || *(bult  + 1) == 34 || *(bult + 1) == '\0' || *(bult + 1) == ' ')))))
        {
            bult++;
            count++;
        }
        if (*bult == '\0')
            break ;
        else
        {
            if (which_quote == 0)
                str = ft_split(bult, ' ');
            else if (which_quote == 1)
            {
                if (*(str = ft_split(bult, ' ')) != NULL)
                {
                    if (*(str = ft_split(str[0], '\'')) != NULL)
                        str = ft_split(str[0], '"');
                }
            }
            if (*str != NULL)
            {
                j = 0;
                while (env[j])
                {
                    tab = ft_split(env[j], '=');
                    if (ft_strcmp(tab[0], take_first_word(str[0] + 1)) == 0)
                    {
                        count += ft_strlen(tab[1]);
                        i = 1;
                        break ;
                    }
                    j++;
                }
            }
            if (*bult == '$' && *(bult + 1) != '\0')
            {
                bult++;
                while (ft_isalnum(*bult) == 1 && *bult)
                    bult++;
                while (*bult)
                {
                    count++;
                    bult++;
                }
            }
        }
    }
    return (count);
}*/

/*
int    allocate_return_parsed(char **bult)
{
    int i;

    char *str;

    i = 0;
    while (*bult)
    {
        if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
        {
           i += ft_strlen(*bult);
        }
        else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2 && find(*bult, '$') == 0)
        {
            if (**bult == '\'')
                *bult = ft_strtrim(*bult, "'");
            else
                *bult = ft_strtrim(*bult, "\"");
            i += ft_strlen(*bult);
        }
        else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2)
        {
            if (**bult == '\'')
            {
                *bult = ft_strtrim(*bult, "'");
                i += ft_strlen(*bult);
            }
            else
            {
                *bult = ft_strtrim(*bult, "\"");
                i += print_env_two(*bult, env, 1, status);
            }
        }
        else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
        {
            //printf("here2 \n");
            if (**bult == 39)
            {
                *bult = trim_once(*bult);
                which_quote = 39;
            }
            else if (**bult == 34)
            {

                *bult = trim_once(*bult);
                which_quote = 34;
            }
            //if ((find(*bult, '$') == 0 && find_dollar_esacpe(*bult, '$') == 0) || which_quote == 39)
            if ((find_without(*bult, '$') == 0 && find_without(*bult, '"') == 0 && find_without(*bult, '\'') == 0) || which_quote == 39)
            {
                //ft_printf("here1\n");
                if (find_without(*bult, '\\') == 0 || which_quote == 39)
                {
                    //ft_printf("here2\n");
                    //if (i == 1)
                      //  write(1, " ", 1);
                    i += ft_strlen(*bult);
                }
                else
                {
                    //ft_printf("here\n");
                    while (**bult != '\0')
                    {
                        if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"' || *(*bult + 1) == '\'' || *(*bult + 1) == '\\'))
                        {
                            //ft_printf("here\n");
                            j = how_many_escape(*bult);
                            if (j % 2 != 0)
                            {
                                while (*(*bult + 1) == '\\')
                                    (*bult)++;
                            }
                            else
                            {
                                while (**bult == '\\')
                                    (*bult)++;
                            }
                            j /= 2;
                            while (--j >= 0)
                                i++;
                        }
                        if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"' || *(*bult + 1) == '\''))
                        {
                            //ft_printf("here\n");
                            (*bult)++;
                        }
                        else if (**bult == '\\')
                        {
                            i++;
                            (*bult)++;
                        }
                        while (**bult != '\0' && **bult != '\\')
                        {
                            i++;
                            (*bult)++;
                        }
                    }
                }
            }
            else
            {
                //ft_printf("here\n");
                if ((i += print_env_two(*bult, env, 0, status)) == 1)
                    write(1, " ", 1);
            }
        }
        bult++;
    }
}*/

int	print_env_two(char *bult, char **env, int which_quote, char **string)
{
    char	**str;
    int		j;
    char	**tab;
    int		i;
    char    *t;

    i = 0;
    t = malloc(2);
    while (*bult)
    {
        if (*bult == '\\' && *(bult + 1) == '\\')
        {
            j = how_many_escape(bult);
            if (j % 2 != 0)
            {
                while (*(bult + 1) == '\\')
                    (bult)++;
            }
            else
            {
                while (*bult == '\\')
                    (bult)++;
            }
            j /= 2;
            while (--j >= 0)
            {
                *t = '\\';
                t[1] = '\0';
                *string = ft_strjoin(*string, t);
            }
        }
        if (*bult == '\\' && (*(bult + 1) == '$' || *(bult + 1) == '"' || *(bult + 1) == '\''))
        {
            //ft_printf("here\n");
            bult++;
            *t = *(bult++);
            t[1] = '\0';
            *string = ft_strjoin(*string, t);
            //my_putchar(*(bult++));
        }
        while (*bult != '$' && *bult != '\0' && (*bult != '\\' || *(bult + 1) != '\\') && (*bult != '\\' || *(bult + 1) != '$') && (*bult != '\\' || *(bult + 1) != '\'') && (*bult != '\\' || *(bult + 1) != '"'))
        {
            *t = *(bult++);
            t[1] = '\0';
            *string = ft_strjoin(*string, t);
            //my_putchar(*(bult++));
        }
        if (*bult == '\\' && (*(bult + 1) == '\\' || *(bult + 1) == '$'))
            continue ;
        if ((*bult == '$' && ((which_quote == 0 && (*(bult + 1) == '\0' || *(bult + 1) == ' ')) || (which_quote == 1 && (*(bult  + 1) == 39 || *(bult  + 1) == 34 || *(bult + 1) == '\0' || *(bult + 1) == ' ')))))
        {
            *t = *(bult++);
            t[1] = '\0';
            *string = ft_strjoin(*string, t);
        }
            //my_putchar(*(bult++));
        if (*bult == '\0')
            break ;
        else
        {
            if (which_quote == 0)
                str = ft_split(bult, ' ');
            else if (which_quote == 1)
            {
                if (*(str = ft_split(bult, ' ')) != NULL)
                {
                    if (*(str = ft_split(str[0], '\'')) != NULL)
                        str = ft_split(str[0], '"');
                }
            }
            if (*str != NULL)
            {
                j = 0;
                while (env[j])
                {
                    tab = ft_split(env[j], '=');
                    if (ft_strcmp(tab[0], take_first_word(str[0] + 1)) == 0)
                    {
                        //ft_putstr(tab[1]);
                        *string = ft_strjoin(*string, tab[1]);
                        i = 1;
                        break ;
                    }
                    j++;
                }
            }
            if (*bult == '$' && *(bult + 1) != '\0')
            {
                bult++;
                while (ft_isalnum(*bult) == 1 && *bult)
                    bult++;
                while (*bult)
                {
                    //my_putchar(*bult);
                    *t = *(bult++);
                    t[1] = '\0';
                    *string = ft_strjoin(*string, t);
                    //bult++;
                }
            }
        }
    }
    return (i);
}


char    *return_parsed(char **bult, char **env)
{
    int i;
    char *str;
    int j;
    int which_quote;
    char *t;

    i = 0;
    which_quote = 0;
    j = 0;
    if (!(t = (char *) malloc(sizeof (char) * 2)))
        return (NULL);
   if (!(str = (char *) malloc(1)))
       return (NULL);
    *str = '\0';
    while (*bult)
    {
        if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
        {
             str = ft_strjoin(str, *bult);
        }
        else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2 && find(*bult, '$') == 0)
        {
            if (**bult == '\'')
                *bult = ft_strtrim(*bult, "'");
            else
                *bult = ft_strtrim(*bult, "\"");
            str = ft_strjoin(str, *bult);
        }
        else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2)
        {
            if (**bult == '\'')
            {
                *bult = ft_strtrim(*bult, "'");
                str = ft_strjoin(str, *bult);
            }
            else
            {
                *bult = ft_strtrim(*bult, "\"");
                print_env_two(*bult, env, 1, &str);
            }
        }
        else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
        {
            //printf("here2 \n");
            ft_printf("Enters\n");
            if (**bult == 39)
            {
                *bult = trim_once(*bult);
                which_quote = 39;
            }
            else if (**bult == 34)
            {

                *bult = trim_once(*bult);
                which_quote = 34;
            }
            //if ((find(*bult, '$') == 0 && find_dollar_esacpe(*bult, '$') == 0) || which_quote == 39)
            if ((find_without(*bult, '$') == 0 && find_without(*bult, '"') == 0 && find_without(*bult, '\'') == 0) || which_quote == 39)
            {
                //ft_printf("here1\n");
                if (find_without(*bult, '\\') == 0 || which_quote == 39)
                {
                    //ft_printf("here2\n");
                    /* if (i == 1)
                         write(1, " ", 1);*/
                    str = ft_strjoin(str, *bult);
                }
                else
                {
                    //ft_printf("here\n");
                    while (**bult != '\0')
                    {
                        if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"' || *(*bult + 1) == '\'' || *(*bult + 1) == '\\'))
                        {
                            //ft_printf("here\n");
                            j = how_many_escape(*bult);
                            if (j % 2 != 0)
                            {
                                while (*(*bult + 1) == '\\')
                                    (*bult)++;
                            }
                            else
                            {
                                while (**bult == '\\')
                                    (*bult)++;
                            }
                            j /= 2;
                            while (--j >= 0)
                            {
                               t[0] = '\\';
                               t[1] = '\0';
                               str = ft_strjoin(str, t);
                            }
                        }
                        if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"' || *(*bult + 1) == '\''))
                        {
                            //ft_printf("here\n");
                            (*bult)++;
                        }
                        else if (**bult == '\\')
                        {
                            *t = **bult;
                            t[1] = '\0';
                            str = ft_strjoin(str, t);
                            (*bult)++;
                        }
                        while (**bult != '\0' && **bult != '\\')
                        {
                            t[0] = **bult;
                            t[1] = '\0';
                            str = ft_strjoin(str, t);
                           (*bult)++;
                        }
                    }
                }
            }
            else
            {
                //ft_printf("here\n");
                if ((print_env_two(*bult, env, 0, &str)) == 1)
                    write(1, " ", 1);
            }
        }
        bult++;
    }
    return (str);
}

char	*take_first_word_re(char *s)
{
    char	*string;
    int		i;
    int		j;

    i = 0;
    j = 0;
    if (s == NULL)
        return NULL;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;
    while (s[i])
    {
        if (s[i] == '\'')
        {
            i++;
            while (s[i] && s[i] != '\'')
                i++;
            if (s[i] == '\'')
                i++;
        }
        else if (s[i] == '"')
        {
            i++;
            while (s[i] && s[i] != '"')
                i++;
            if (s[i] == '"')
                i++;
        }
        else if (ft_isalnum(s[i]) || s[i] == '/')
            i++;
        else
            break;
    }
    //this has been replaced by bellow
    /*while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"') && s[i])
        i++;*/
    if (!(string = malloc(i + 1)))
        return (0);
    i = 0;
    /*while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;*/
    /*while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"' || s[i] == '\\') && s[i])
        string[j++] = s[i++];*/
    /*while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;*/
    while (s[i])
    {
        if (s[i] == '\'')
        {
            string[j++] = s[i++];
            while (s[i] && s[i] != '\'')
                string[j++] = s[i++];
            if (s[i] == '\'')
                string[j++] = s[i++];
        }
        else if (s[i] == '"')
        {
            string[j++] = s[i++];
            while (s[i] && s[i] != '"')
                string[j++] = s[i++];
            if (s[i] == '"')
                string[j++] = s[i++];
        }
        else if (ft_isalnum(s[i]) || s[i] == '/')
            string[j++] = s[i++];
        else
            break;
    }
    string[j] = '\0';
    return (string);
}

char	*ft_strjoin_re(char const *s1, char const *s2)
{
    int		i;
    int		j;
    int     check;
    char	*str;

    check = 0;
    if (s1 == NULL || s2 == NULL)
        return (NULL);
    i = ft_strlen(s1) + ft_strlen(s2) + 1;
    if (i == 1)
        check = 1;
    str = (char *)malloc(sizeof(char) * i);
    if (str == NULL)
        return (str);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    if (check == 0)
        str[i++] = ' ';
    j = 0;
    while (s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    return (str);
}

char	*skip_first_word_re(char *str)
{
    char	*s;
    int		i;
    int		j;
    int len;

    i = 0;
    j = 0;
    if (str[i] != '\0')
    {
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
            i++;
        if (str[i] == ' ')
            i++;
        /*while (((*str)[i] == ' ' || (*str)[i] == '\t') && (*str)[i] != '\0')
            i++;*/
        len = ft_strlen(str);
        s = ft_calloc(sizeof (char ), len - i);
        //s[j++] = str[i++];
        while (i < len)
        {
            s[j] = str[i];
            i++;
            j++;
        }
        s[j] = '\0';
        /*this free causes a problem !!
        if (*str)
            free(*str);*/
        return (s);
    }
    return (str);
}

int     check_bin_echo(char *str)
{
    if (ft_strncmp(str, "/bin/echo", ft_strlen("/bin/echo")) == 0 && str[ft_strlen("/bin/echo")] == ' ')
        return (1);
    return (0);
}