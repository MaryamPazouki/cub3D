/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-07 14:31:55 by mpazouki          #+#    #+#             */
/*   Updated: 2024-07-07 14:31:55 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

int	lst_size(t_list *lst)
{
	int	i;
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst-> content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				++len;
				return (len);
			}
			++len;
			++i;
		}
		lst = lst->next;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, char *new_buf, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(lst[fd]);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		lst[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->content = new_buf;
	new_node->next = NULL;
}

int	is_newline(t_list *lst)
{
	int	i;

	if (NULL == lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] && i < BUFFER_SIZE)
		{
			if (lst->content[i] == '\n')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

void	create_list(t_list **lst, int fd)
{
	char	*text_buf;
	int		read_size;

	while (!is_newline(lst[fd]))
	{
		text_buf = malloc(BUFFER_SIZE + 1);
		if (NULL == text_buf)
			return ;
		read_size = read(fd, text_buf, BUFFER_SIZE);
		if (!read_size)
		{
			free(text_buf);
			if (read_size < 0)
				clear_list(&lst[fd], NULL, NULL);
			return ;
		}
		text_buf[read_size] = '\0';
		ft_lstadd_back(lst, text_buf, fd);
	}
}
