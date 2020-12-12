/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:19:17 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/12 17:44:00 by molabhai         ###   ########.fr       */
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


int		check_pwd(char *str)
{
	int i;
	char *s;
	int on;

	i = 0;
	on = 0;
	str = ft_toStrLower(str);
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
	

void	pwd_command(void)
{
	char *str;

	if (!(str = (char *) ft_calloc(sizeof(char), 100)))
		return ;
	if (getcwd(str, 100) == NULL)
		ft_printf("Error in command\n");
	else
		ft_printf("%s\n", str);
	free(str);
}
