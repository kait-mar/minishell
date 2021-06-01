#ifndef ESCAPE_CHARACTER_H
# define ESCAPE_CHARACTER_H

int		count_escape(char *str, int i);
int		new_space_dquote(char *str, int count, int *i);
int		new_space_quote(char *str, int count, int *i);
int		new_space_core(char *str, int count, int *i);
void	increment(int *count, int *i);
int		new_space(char *str);
void	escape_normal_core(char *str, char **string, int *i, int *j);
void	escape_normal_dquote(char *str, char **string, int *i, int *j);
void	escape_normal_head(char *str, char **string, int *i, int *j);
int		count_meta_quote(char *str, int count, int *i);
int		count_with_mod(char *str, int count, int *i, int *nbr);
int		count_meta_space(char *str);
void	escape_meta_head(char *str, char **string, int *i, int *j);
void	escape_meta_core(char *str, char **string, int *i, int *j);
int		count_dollar_core(char *s, int count, int *i);
void	remove_escape_dollar_support(char **str, char *s, int *i, int *j);
int		in_quote(char *str, int i);
void	remove_escape_loop(char **str, char *s, int *i, int *j);
void	escape_core_support(char *str, char **string, int *i, int *j);
char	*es_for_quote(char *s);

#endif