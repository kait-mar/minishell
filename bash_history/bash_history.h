/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_history.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:51:09 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/12 16:51:10 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASH_HISTORY_H
# define	BASH_HISTORY_H

typedef struct s_history
{
	char	*term_type;
	char	*tty_name;
	char	*key_s;
	char	*key_e;
	char	*up_arrow;
	char	*down_arrow;
	char	*clear;
	char	*line_start;
	char	*delete_char;
	char	*delete_mode;
	char	*exit_d_mode;
	int		fd;
}				t_history;

typedef struct s_assen
{
	char			*cmd;
	struct s_assen	*next;
	struct s_assen	*prev;
}				t_assen;

typedef struct s_glb
{
	t_history	history;
	t_assen		*climb;
}				t_glb;

struct termios	tty_init(int fd);
t_assen			*read_l(char **temp, char **tmp, t_glb glb, char *str);
char			*tty_loop(t_assen *assen,
					t_glb glb, char *string);
t_assen			*arrow_down(t_history history,
					t_assen *climb, char **tmp, char **temp);
t_assen			*arrow_up(char **tmp, t_history history, t_assen *climb);
void			back_space(char **tmp, t_history history,
					char **temp, t_assen *climb);
void			string_extention(char **tmp, char **temp, char *str);
char			*reading_input(t_assen *assen, char *string, t_history history);
void			filling(t_assen *assen);
char			*delete_char(char *string);
int				find_re(char *string, int c);
char			*extend_re(char *str, char *s);
int				int_put(int c);
t_history		init_hist(t_history history);
void			append_assen(t_assen **assen, char *cmd);
char			*string_extention_helper(char *temp);
char			*read_l_support(char **temp, char **tmp);
char			*ctrl_d(void);
int				condition_command(t_glb glb, char *str);
void			signals_in_read(char **tmp, char **temp, char *str);

#endif
