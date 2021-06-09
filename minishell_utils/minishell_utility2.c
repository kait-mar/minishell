#include "../minishell.h"

t_split	count_new_initializer(char *str)
{
	t_split	split;

	split.i = 0;
	split.count = 0;
	split.end = 0;
	split.start = 0;
	while (str[split.i] == ' ')
		split.i += 1;
	split.start = split.i;
	split.count = split.start;
	return (split);
}

static	int	ret_split(t_split split)
{
	split.count -= (split.start + split.end);
	if (split.count < 0)
		split.count = 0;
	return (split.count);
}

int	count_new(char *str)
{
	t_split	split;
	int		on;

	split = count_new_initializer(str);
	on = 0;
	while (str[split.i] != '\0')
	{
		if (str[split.i] != ' ')
			on = 1;
		if (str[split.i + 1] == '\0' && str[split.i] == ' ' && on == 1)
		{
			split.j = split.i;
			while (str[split.j] == ' ')
			{
				split.j -= 1;
				split.end += 1;
			}
			if (str[split.j] == '\\')
				split.end -= 1;
		}
		split.i += 1;
		split.count += 1;
	}
	split.count = ret_split(split);
	return (split.count);
}
