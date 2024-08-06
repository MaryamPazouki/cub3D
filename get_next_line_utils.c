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
#include <stdio.h>

int	lst_size(t_list *lst)
{
	int i;
	int len;

	if(!lst)
		return(0);
	len = 0;
	while(lst)
	{
		i=0;
		while(lst-> content[i] != '\0')
		{
			if(lst->content[i] == '\n')
			{
				++len;
				return(len);
			}
			++len;
			++i;
		}
		lst = lst->next;
	}
	return(len);
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


void	ft_lstadd_back(t_list **lst, char *new_buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*lst);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*lst = new_node;
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

	while(!is_newline(*lst))
	{
		text_buf = malloc(BUFFER_SIZE + 1);
		if(NULL== text_buf)
			return ;
		read_size = read(fd, text_buf, BUFFER_SIZE);
		if(!read_size)
		{
			free(text_buf);
			return ;
		}
		text_buf[read_size] = '\0';
		ft_lstadd_back(lst, text_buf);
	}
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

char	*get_line(t_list *list)
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

// void node_with_nl(t_list **lst)
// {
// 	t_list *last_node;
// 	t_list *nl_node;
// 	char *buf;
// 	int i;
// 	int j;

// 	if (!lst || !*lst)
// 		return;
// 	last_node = ft_lstlast(*lst);

// 	i = 0;
// 	while (last_node->content[i] != '\n' && last_node->content[i])
// 		++i;
// 	if (!last_node->content[i])
// 		return;
// 	buf = malloc(BUFFER_SIZE + 1);
// 	nl_node = malloc(sizeof(t_list));
// 	if (!buf || !nl_node)
// 		return;
// 	j = 0;
// 	while (last_node->content[i] && last_node->content[++i])
// 		buf[j++] = last_node->content[i];
// 	buf[j] = '\0';
// 	nl_node->content = buf;
// 	nl_node->next = NULL;
// 	clear_list(lst, nl_node, buf);
// }
void node_with_nl(t_list **lst)
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

void clear_list(t_list **lst, t_list	*clean_node,char	*buf)
{
	t_list *tmp;

	if (*lst == NULL)
		return ;
	while(*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node->content[0])
		*lst = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
