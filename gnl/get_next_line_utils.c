/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:49:05 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/05 11:35:51 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

void	ft_lstadd_back_gnl(t_gnl_list **lst, void *data)
{
	t_gnl_list	*last;
	t_gnl_list	*ret;

	ret = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!ret)
		return ;
	ret->content = data;
	ret->next = NULL;
	if (ret == NULL)
	{
		return ;
	}
	last = *lst;
	while (last && last->next != NULL)
		last = last->next;
	if (last == NULL)
		*lst = ret;
	else
		last->next = ret;
}

int	gnl_lstclear(t_gnl_list **lst, void (*del)(void *))
{
	t_gnl_list	*nxt;

	if (!lst || !*lst || !del)
		return (0);
	nxt = *lst;
	while (*lst != NULL)
	{
		nxt = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		*lst = nxt;
	}
	return (0);
}

int	ft_strcpy_len(char **dst, char *src, int len)
{
	char	*temp;
	int		i;

	temp = *dst;
	i = 0;
	while (*temp)
	{
		temp++;
	}
	while (i < len - 1 && *(src + i))
	{
		*(temp + i) = *(src + i);
		i++;
	}
	if (*(src + i) == '\n')
	{
		*(temp + i) = *(src + i);
		*(temp + i + 1) = '\0';
	}
	else
		*(temp + i) = '\0';
	return (i);
}
