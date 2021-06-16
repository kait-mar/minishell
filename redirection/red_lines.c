//
// Created by Mouaad Labhairi on 6/12/21.
//

#include "../minishell.h"

t_meta	*red1(t_meta *meta, int *on)
{
	t_meta	*temp;

	temp = meta;
	*on = 0;
	return (temp);
}

t_meta	*red2(t_meta *temp, char **env)
{
	temp = temp->next;
	temp->argument = chang_dollar_sign(temp->argument, env);
	return (temp);
}

t_meta	*red3(t_meta *meta, int fd)
{
	g_global.redirect_fd = fd;
	if (fd == -1 && meta != NULL && meta->next != NULL)
		meta = meta->next;
	return (meta);
}

void 	red4(void)
{
	if (g_global.redirect_fd == -1)
	{
		close(g_global.fd[1]);
		g_global.redirect_fd = 0;
	}
}
