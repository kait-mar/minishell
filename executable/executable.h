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

#endif
