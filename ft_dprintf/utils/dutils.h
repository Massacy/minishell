/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dutils.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:31:28 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/04 06:27:11 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUTILS_H
# define DUTILS_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

size_t	dcheck_x_x(int fd, va_list *arg_ptr, const char *format);
size_t	dcheck_u(int fd, va_list *arg_ptr);
size_t	dcheck_d_i(int fd, va_list *arg_ptr);
size_t	dcheck_p(int fd, va_list *arg_ptr);
size_t	dcheck_s(int fd, va_list *arg_ptr);
size_t	dcheck_c(int fd, va_list *arg_ptr);

void	ft_reverse(char *str);
char	trans_itoh_char(uintptr_t num, bool is_upper);
void	transform_ptr_to_hexadecimal(uintptr_t num, bool is_upper, char *str);
void	transform_uint_to_hexadecimal(unsigned int num, bool is_upper,
			char *str);

size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);

#endif
