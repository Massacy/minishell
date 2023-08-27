/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:07:04 by imasayos          #+#    #+#             */
/*   Updated: 2022/10/02 05:48:17 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*create_new_lst(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	if (new_lst == NULL)
		return (NULL);
	new_lst->content = f(lst->content);
	if (del != NULL)
		del(lst->content);
	return (new_lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_new_lst;
	t_list	*new_lst;
	t_list	*ptr;
	t_list	*pre_new_lst;

	if (lst == NULL || f == NULL)
		return (NULL);
	first_new_lst = create_new_lst(lst, f, del);
	if (first_new_lst == NULL)
		return (NULL);
	pre_new_lst = first_new_lst;
	ptr = lst->next;
	while (ptr != NULL)
	{
		new_lst = create_new_lst(ptr, f, del);
		if (new_lst == NULL)
			return (NULL);
		pre_new_lst->next = new_lst;
		pre_new_lst = new_lst;
		ptr = ptr->next;
	}
	return (first_new_lst);
}
