/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:09:27 by imasayos          #+#    #+#             */
/*   Updated: 2022/10/02 05:54:30 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_ptr;

	if (new == NULL)
		return ;
	last_ptr = ft_lstlast(*lst);
	if (last_ptr == NULL)
	{
		*lst = new;
		return ;
	}
	last_ptr->next = new;
}
