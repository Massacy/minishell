/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 08:42:08 by imasayos          #+#    #+#             */
/*   Updated: 2022/10/02 05:54:14 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*p;

	p = lst;
	if (p == NULL)
		return (0);
	cnt = 1;
	while (p->next != NULL)
	{
		p = p->next;
		cnt++;
	}
	return (cnt);
}
