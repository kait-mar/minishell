/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:13:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 10:06:39 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_file(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != ' ')
    {
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '\0' && str[i] != '"')
                i++;
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] !=  '\0' && str[i] != '\'')
                i++;
        }
       i++;
    }
    return (i);
}

char    *file_name(char *str)
{
    char *name;
    int  i;
    int    j;

    i = 0;
    j = count_file(str);
    name = ft_calloc(1, j + 1);
    j = 0;
    while (str[i] != '\0' && str[i] != ' ')
    {
        if (str[i] == '"')
        {
            name[j++] = str[i++];
            while (str[i] != '\0' && str[i] != '"')
                name[j++] = str[i++];
        }
        else if (str[i] == '\'')
        {
            name[j++] = str[i++];
            while (str[i] !=  '\0' && str[i] != '\'')
                name[j++] = str[i++];
        }
        name[j++] = str[i++];
    }
    return (name);
}

char    *remove_staring_quote(const char *s)
{
    int i;
    char *str;
    int    k;
    int     j;

    i = 0;
    if (*s == '"')
    {
        while (s[i] == '"')
            i++;
    }
    else if (*s == '\'')
    {
        while (s[i] == '\'')
            i++;
    }
    j = ft_strlen(s) - (2 * i);
    str = ft_calloc(j + 1, 1);
    i = 0;
    k = 0;
    if (*s == '"')
    {
        while (s[i] == '"')
            i++;
    }
    else if (*s == '\'')
    {
        while (s[i] == '\'')
            i++;
    }
    //return (ft_substr(s, i, j));
    while (--j >= 0)
    {
        str[k] = s[i];
        k++;
        i++;
    }
    str[k] = '\0';
    return (str);
}

t_meta  *append_file(t_meta *meta, char *str, char **env, int *status)
{
    int fd;
    //char *output_from;
    char **split;
    char *output_to;
    pid_t pid;
    t_meta *head;
    char *new;
    int i;
    int on;

    head = meta;
    i = 0;
    on = 0;
    //output_from = ft_strdup(head->argument);
    while (head->meta_append != 0)
    {
        head = head->next;
        i += 1;
       head->argument = ft_strtrim(head->argument, " ");
        head->argument = chang_dollar_sign(head->argument, env);
        new = file_name(head->argument);
        head->argument = head->argument + ft_strlen(new);
        if (meta->command == 0 && check_wich_command(take_first_word(head->argument)) != 0 && on == 0)
        {
            meta = head;
            on = 1;
            meta->command = check_wich_command(take_first_word(ft_strtrim(head->argument, " ")));
        }
        new = final_file_name(new);
       if (on == 0)
        {
            meta->argument = ft_strjoin(meta->argument, " ");
            meta->argument = ft_strjoin(meta->argument, head->argument);
        }
        /*if (*output_to == '\'')
            output_to = ft_strtrim(output_to, "'");
        else if (*output_to == '"')
            output_to = ft_strtrim(output_to, "\"");*/
       /* split = ft_split(output_to, ' ');
        free(output_to);
        output_to = NULL;
        output_to = ft_strdup(split[0]);
        while (split[i] != NULL)
        {
            split[i] = ft_strjoin(" ", split[i]);
            output_to = ft_strjoin(output_to, split[i]);
            i += 1;
        }*/
        i = 1;
        if ((fd = open(new, O_CREAT | O_APPEND | O_RDWR, S_IRWXU)) == -1)
        {
            ft_printf("%s", strerror(errno));
            return (NULL);
        }
    }
    if ((pid = fork()) < 0)
        ft_printf("%s\n", strerror(errno));
    else if (pid == 0)
    {
        if (dup2(fd, 1) == -1)
            ft_printf("%s\n", strerror(errno));
        built_in(meta, str, env, status, 0);
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (waitpid(pid, status, WUNTRACED) == -1)
            ft_printf("Error has occured\n");
        close(fd);
    }
    while (i  != 0)
    {
        meta = meta->next;
        i -= 1;
    }
    return (meta);
}
