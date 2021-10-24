/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:17:59 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/06 14:13:24 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!(new))
		return (NULL);
	res = new;
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!(new))
		{
			ft_lstclear(&new, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&res, new);
	}
	return (res);
}
