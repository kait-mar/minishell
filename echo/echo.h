#ifndef ECHO_H
# define ECHO_H

int		first_word_lenght(char *s);
int		fill_first_word(char *s, char **string, int *i, int *j);
char	*which_trim(char *bult, int *which_quote);
void	last_put_cases(char **bult, char **env, int *status, int *i);
char	*in_between_cases(char *bult, char **env, int *status);
int		print_env_condition(char *bult);
int		which_quote_condition(char *bult, int which_quote);
char	*last_print_env_case(char *bult, char **env,
			int which_quote, int *status);
int		check_echo_flag(char **bult, int *i);
void	echo_complet(char **bult, char **env, int *status, int i);
void	to_free(char **bult);
int		condition1(char **bult, int k);
int		condition2(char **bult, int k);
char	**put_cases_norminette(char **bult);
int		last_put_condition(char **bult, int which_quote);
char	*es_quote(char *s);

#endif