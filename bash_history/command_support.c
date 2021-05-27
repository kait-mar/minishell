#include "../minishell.h"

char	*read_l_support(char **temp, char **tmp, t_glb glb)
{
	if (g_global.signal_input == 1)
	{
		free(*tmp);
		free(*temp);
		*tmp = NULL;
		*temp = NULL;
		g_global.signal_input = 0;
	}
	*tmp = ctrl_d();
	return (*tmp);
}

int	condition_command(t_glb glb, char *str)
{
	return ((glb.history.down_arrow != NULL
			&& ft_memcmp(str, glb.history.down_arrow, 3) != 0)
		&& (glb.history.up_arrow != NULL
			&& ft_memcmp(str, glb.history.up_arrow, 3) != 0) && str[0] != 127);
}
