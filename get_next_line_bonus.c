/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 10:25:56 by mpazouki          #+#    #+#             */
/*   Updated: 2024-08-07 10:25:56 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <stdio.h>

void	clear_list(t_list **lst, t_list	*clean_node, char	*buf)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node != NULL && clean_node->content != NULL
		&& clean_node->content[0] != '\0')
		*lst = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

void	node_with_nl(t_list **lst)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = ft_lstlast(*lst);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	clear_list(lst, clean_node, buf);
}

void	copy_str(t_list *lst, char *str)
{
	int	i;
	int	k;

	if (NULL == lst)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = lst->content[i++];
		}
		lst = lst->next;
	}
	str[k] = '\0';
}

char	*get_line_new(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = lst_size(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_list	*lst[4096];
	char			*line;

	if (fd < 0 || fd >= 4095 ||BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		if(fd >= 0 && fd < 4095)
			clear_list(&lst[fd], NULL, NULL);
		return (NULL);
	}
	create_list(&lst, fd);
	if (!lst[fd])
		return (NULL);
	line = get_line_new(lst[fd]);
	node_with_nl(&lst[fd]);
	return (line);
}
