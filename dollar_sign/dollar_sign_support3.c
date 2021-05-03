#include "../minishell.h"

char	*string_oldpwd(int *on)
{
	char	*string;

	string = NULL;
	if (g_global.check == 0)
		string = ft_strdup("");
	else
	{
		string = ft_strdup(g_global.oldpwd_only);
		string = take_after_equal(string);
		*on = 1;
	}
	return (string);
}

char	*string_pwd(int *on)
{
	char	*string;

	string = NULL;
	string = ft_strdup(g_global.pwd_only);
	string = take_after_equal(string);
	*on = 1;
	return (string);
}

char	*string_frees(char *string, int escape, char *ss, int on)
{
	char	*string_free;

	if (escape > 0)
	{
		if (on == 1)
		{
			string_free = string;
			string = adding_escape(string, escape);
			free(string_free);
		}
		else
			string = adding_escape(ss, escape);
	}
	return (string);
}
