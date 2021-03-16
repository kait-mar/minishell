/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:19:17 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/22 18:17:22 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


char 	*ft_toStrLower(char *str)
{
	char *s;
	int	i;

	i = 0;
	if (!(s = (char *) malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' &&  str[i] <= 'Z')
			s[i] = (str[i] + 32);
		else
			s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

static  int ft_isupper(int c)
{
    if (c >= 65 && c <= 90)
        return (1);
    return (0);
}

int     check_first_pwd(char *str)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (ft_isupper(str[i]) == 1)
            return (1);
        i += 1;
    }
    return (0);
}

int     check_after_first(char *str)
{
    int i;

    i = 3;
    while (str[i] != '\0')
    {
        if (ft_isprint(str[i]) == 1)
            return (1);
        i += 1;
    }
    return (0);
}

int		check_pwd(char *str, int *exept)
{
	int i;
	char *s;
	int on;

	i = 0;
	*exept = 0;
	on = 0;
	if (check_first_pwd(str) == 1)
	    if (check_after_first(str) == 1)
	        *exept = 1;
	//str = ft_toStrLower(str);
	s = "pwd";
	while (i < 3)
	{
		if (str[i] != s[i])
			on = 1;
		i += 1;
	}
	if (ft_isalpha(str[i]))
		on = 1;
	return (on);
}
	
void 	pwd_command(int *status, int exept)
{
	char *str;

	if (!(str = (char *) ft_calloc(sizeof(char), 100)))
		return ;
	if (exept == 1)
    {
        *status = 1;
        ft_printf("usage: pwd [-L | -P]\n");
        return ;
    }
	if (getcwd(str, 100) == NULL)
	{
		ft_printf("%s\n", strerror(errno));
		*status = 11;
	}
	ft_printf("%s\n", str);
	free(str);
	str = NULL;
	*status = 0;
}