#include "../minishell.h"

int	condition1(char **bult, int k)
{
	return (bult[g_global.j_echo][k] == '\\'
			&& (bult[g_global.j_echo][k + 1] == '$'
			|| bult[g_global.j_echo][k + 1] == '"'
			|| bult[g_global.j_echo][k + 1] == '\''
			|| bult[g_global.j_echo][k + 1] == '\\'));
}

int	condition2(char **bult, int k)
{
	return (bult[g_global.j_echo][k] == '\\'
			&& (bult[g_global.j_echo][k + 1] == '$'
			|| bult[g_global.j_echo][k + 1] == '"'
			|| bult[g_global.j_echo][k + 1] == '\''));
}
