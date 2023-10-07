/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiyu <smiyu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:06:29 by smiyu             #+#    #+#             */
/*   Updated: 2023/10/06 23:24:22 by smiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

// get_next_line_bonus.c
char	*get_next_line(int fd);

// get_next_line_util.c
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlcpy(char *dest, const char *src, size_t dstsize);
char	*gnl_strdup(char *s);
char	*gnl_strjoin(char const *s1, char const *s2);

#endif