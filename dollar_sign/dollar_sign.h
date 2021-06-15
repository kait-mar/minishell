#ifndef DOLLAR_SIGN_H
# define DOLLAR_SIGN_H

typedef struct s_sign
{
	int		remove;
	int		space_front;
	int		space_back;
	int		on;
	int		valid;
	int		i;
	int		j;
	char	*s;
	char	*string;
	int		len_before;
	int		len_after;
	int		len_cmd;
	int		error;
}			t_sign;

int		count_escap(char *s);
char	*adding_escape(char *s, int count);
int		dollar_len(char *str, int i);
char	*take_word(char *str, int i, int len);
int		dollar_parsing(char *s);
t_sign	change_valid(t_sign lst, char *str, char **env);
char	*chang_dollar(char *s, char **env, int *on);
t_sign	change_dollar_helper(t_sign lst, char **str, char **env);
char	*realloc_input(char *str, int string_len, t_sign lst);
t_sign	change_dollar_core(t_sign lst, char **str, char **env);
char	*take_away_dollar(char *s);
void	take_after_equal_support(char *s, int *i, int *k, int *j);
char	*take_after_equal(char *s);
char	*string_change_dollar(char *ss, int *on, char **env);
char	*string_oldpwd(int *on);
char	*string_pwd(int *on);
char	*string_frees(char *string, int escape, char *ss, int on);
t_sign	realloc_list(char *str, t_sign lst);
t_sign	realloc_list_support(char *str, t_sign lst, int *j);
t_sign	change_valid_norminette(t_sign lst, char *str);
char	*str_free(char *str, char *s);
int		check_front_quote(char *s, int i);
int		last_condition(t_sign lst, char *str);

#endif