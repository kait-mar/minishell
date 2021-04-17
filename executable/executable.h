/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:23:12 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 14:23:13 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTABLE_H
# define EXECUTABLE_H

void	no_slash(char **splits);
void	is_directory(char **splits);
void	nothing(char **splits);
int		check_for_bin(char *path);
int		exec_loop(char **commands, char **splits, char *path, char **env);
int		check_slash(char *s);
void	exec_error(char **splits, char **commands, int i, char **env);
void	exec_exec(char **splits, char **commands, char **env);
char	*return_parse(char **splits, char **env);
char	*filling_path(char **env, int *on);
void	execution(char **splits, char *str, char **env);
char	*first_return(char *bult, char **string);
char	*second_return(char *bult, char **string);
char	*third_return(char *bult, char **string);
char	*forth_return(char *bult, char **string);
void	final_func(char *bult, char **string);
int		wich_quote_func(char **env, char **string, char *bult, int wich_quote);
char	*print_env_loop(char *bult, char **string, int wich_quote);
char	*parsed_func1(char **bult, char *str);
int		print_env_two(char *bult, char **env, int which_quote, char **string);
void	parsed_func2(char **bult, char **str, char **env);
void	parsed_func3(char **bult, int *which_quote);
char	*parsed_func4(char **bult, char *str);
char	*parsed_func5(char **bult, char *str);
char	*parsed_func6(char **bult, char *str);
void	parsing(char **bult, int which_quote, char **str, char **env);

#endif
