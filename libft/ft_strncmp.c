/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:54:43 by imasayos          #+#    #+#             */
/*   Updated: 2022/09/07 09:52:26 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	int n1;
// 	int n2;

// 	if (n <= 0)
// 		return (0);
// 	while (n != 1 && *s1 == *s2 && *s1 != '\0' && *s2 != '\0')
// 	{
// 		s1++;
// 		s2++;
// 		n--;
// 	}
// 	n1 = *s1;
// 	n2 = *s2;
// 	if (n1 < 0)
// 		n1 += 256;
// 	if (n2 < 0)
// 		n2 += 256;
// 	return (n1 - n2);
// }

#include<stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n <= 0)
		return (0);
	while (n != 1 && *s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
