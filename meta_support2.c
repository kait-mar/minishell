#include "minishell.h"

t_meta	*split_it_header(char **splits, t_meta *global, int *i)
{
	if (check_meta(splits[*i]) == TRUE)
		global = meta_in(splits, global, i);
	else if (check_meta(splits[*i]) == FALSE)
		global = meta_out(splits, global, i);
	global->next = NULL;
	return (global);
}
