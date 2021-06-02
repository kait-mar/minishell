#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

typedef struct s_split
{
	int			i;
	int			j;
	int			k;
	int			l;
	char		**tabs;
	int			count;
	int			check;
	int			start;
	int			end;
}	t_split;

void		count_helper(char *s, char b, int *i, int *count);
int			count_helper1(char *s, int *i, int *count, int *j);
void		count_helper2(char *s, char c, int *i, int *count);
int			count_condition(char *s, int i, char c, char b);
void		increment_counters(int *i, int *k);
t_split		keep_split_support(t_split lst);
t_split		keep_split_support2(char *s, t_split lst, char c, char b);
char		**ft_tofree(char *tabs[], int j);
void		func1(char *s, char c, int *i, int *k);
t_split		keep_split_support3(char *s, t_split lst, char c);
t_split		keep_split_core(char *s, t_split lst, char c, char b);
t_split		increment_counters2(char *s, t_split lst, char c, char b);
t_split		keep_split_supporter(t_split lst, char c, char *s);
int			count_new(char *str);

#endif