/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 22:29:21 by kait-mar          #+#    #+#             */
/*   Updated: 2019/11/15 04:23:31 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 60
# include <stdlib.h>
# include <unistd.h>

char	        *ft_strdup(const char *s1);
char        	*ft_strjoin(char const *s1, char const *s2);
void	        *ft_calloc(size_t count, size_t size);
int		        ft_strlen(const char *str);
char	        *ft_substr(char const *s, int start, int len);
int		        get_next_line(int fd, char **line);
static int		coun(char *s, char c);
static int		len_mot(char *s, char c, int i);
static char		**ft_tofree(char *tab[], int j);
char			**ft_split(char const *s, char c);
int             ft_strcmp(const char *s1, const char *s2);
void	        ft_putstr(char *s);

#endif
