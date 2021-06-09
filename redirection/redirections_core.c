#include "../minishell.h"

char	*fill_name(char *str, char *name)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
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
			while (str[i] != '\0' && str[i] != '\'')
				name[j++] = str[i++];
		}
		name[j++] = str[i++];
	}
	return (name);
}

int	check_redirect_error(char *new, int *fd, int append)
{
	if (g_global.in_redirect == 1)
	{
		ft_printf("Error in file Name \n");
		return (-1);
	}
	if (append != 0)
	{
		*fd = open(new, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
		if ((*fd) == -1)
		{
			ft_printf("%s", strerror(errno));
			return (-1);
		}
	}
	return (*fd);
}
