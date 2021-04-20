#include "../minishell.h"

void     count_helper(char *s, char b, int *i, int *count)
{
    *i += 1;
    while (s[*i] != b && s[*i] != '\0')
        *i += 1;
    if (s[*i] == b)
        *i += 1;
    *count += 1;
}

int     count_helper1(char *s, int *i, int *count, int *j)
{
    if (s[*i] == '\\')
    {
        *j = how_many_escape(s);
        if (*j % 2 == 0)
        {
            count++;
            while (s[*i] == '\\')
                *i += 1;
            return (1) ;
        }
    }
	return (0);
}

int		count_condition(char *s, int i, char c, char b)
{
	return (s[i] != '\0' &&
			((s[i] != c && s[i] != b) || ((s[i] == c || s[i] == b)
			&& i - 1 >= 0 && s[i-1] == '\\')));
}

void	increment_counters(int *i, int *k)
{
	*k += 1;
	*i += 1;
}
