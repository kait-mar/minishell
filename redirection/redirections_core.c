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

char	*free_temp_(char *s)
{
	char	*str;

	str = s;
	s = ft_strdup("");
	free(str);
	return (s);
}

t_meta	*input_conditions(t_meta *meta, char **new, t_meta *temp, int *on)
{
	char	*str;

	*new = file_name(temp->argument);
	str = temp->argument;
	temp->argument = ft_strdup(temp->argument + ft_strlen(*new));
	free(str);
	if ((temp->argument)[0] == ' ')
	{
		str = temp->argument;
		temp->argument = ft_strdup(temp->argument + 1);
		free(str);
	}
	meta = meta_input(meta, temp, on);
	*new = final_file_name(*new);
	if (*on == 0)
	{
		if (input_conditions1(meta, temp))
			meta = input_free(meta);
		str = meta->argument;
		meta->argument = ft_strjoin(meta->argument, temp->argument);
		free(str);
	}
	return (meta);
}

void	checking_out(t_meta *temp, t_meta *meta, char **env, int *j)
{
	if (temp != NULL && temp->meta == '>')
	{
		*j = 1;
		independent_func(temp, meta, env);
	}
}
