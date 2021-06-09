#include "../minishell.h"

int	new_pwd_core(char **env, int *i, char *old_pwd, int *res)
{
	int	k;

	k = 0;
	while (env[*i])
	{
		if (find_pwd(env[*i]) == 1)
		{
			if (*res >= 1)
				free(env[*i]);
			env[*i] = ft_strdup(old_pwd);
			*res += 1;
			k = 1;
			break ;
		}
		*i += 1;
	}
	return (k);
}

char	*old_pwd_core(char **env, int *i, int *j)
{
	char	*take_it;
	char	*s;

	take_it = NULL;
	while (env[*j])
	{
		if (find_pwd(env[*j]) == 1)
		{
			s = ft_strdup(env[*j]);
			take_it = only_after_equal(s);
			free(s);
			*i = 1;
			break ;
		}
		*j += 1;
	}
	return (take_it);
}

int	pwd_core(char **env, int *i, char *old_pwd, int *res)
{
	int	k;

	k = 0;
	while (env[*i])
	{
		if (find_old_pwd(env[*i]) == 1)
		{
			if (*res >= 1)
				free(env[*i]);
			env[*i] = ft_strdup(old_pwd);
			k = 1;
			*res += 1;
			break ;
		}
		*i += 1;
	}
	return (k);
}
