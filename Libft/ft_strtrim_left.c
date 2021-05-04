#include "libft.h"

static int	fct(char s, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static char	*other_return(char const *s1, char const *set)
{
	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		return ((char *)s1);
	else
		return ((char *)set);
}

static char	*return_vr(int end, int start)
{
	char	*vr;

	if (end < start)
	{
		vr = malloc(1);
		if (vr == 0)
			return (0);
		vr[0] = '\0';
		return (vr);
	}
	else
		return (NULL);
}

char	*ft_strtrim_left(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (s1 == NULL || set == NULL)
		return (other_return(s1, set));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (fct(s1[start], (char *)set) != 0)
		start++;
	if (end < start)
		return (return_vr(end, start));
	str = (char *)malloc(end - start + 2);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1 + start, end - start + 1);
	str[end - start + 1] = '\0';
	return (str);
}
