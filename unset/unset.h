#ifndef UNSET_H
# define UNSET_H
typedef struct s_env
{
	char			*in_env;
	struct s_env	*next;
}				t_env;

int		inside_quote(char *s);
int		delete_in_env_helper(char *s, char *split, int *check);
t_env	*delete_in_env_core(t_env *env, char *split, int on);
void	free_struct(t_env *lst);
void	print_error(char *split);
int		check_unset_tok(char *string);

#endif