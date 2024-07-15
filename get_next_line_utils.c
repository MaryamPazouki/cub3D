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

int lst_size(t_list *lst)
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


void	ft_lstadd_back(t_list **lst, char *new_buf)
{
	t_list	*new_node;
    t_list *last;

	if (!lst || !new_buf)
		return ;
     new_node = malloc(sizeof(t_list));
    if(!new_node)
        return ;
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
   
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_node;
    new_node->content = new_buf;
    new_node->next = NULL;
}


int is_newline(t_list *lst)
{
    int i;

    if(!lst)
        return(0);
    i = 0;
    while(lst->content[i] != '\0')
    {
        if(lst->content[i] == '\n')
            return(1);
        ++i;
    }
    return(0);
}

void create_lst(char **lst, int fd)
{
    char *text_buf;
    int read_size;

    while(!is_newline(*lst))
    {
        text_buf = malloc(BUFFER_SIZE + 1);
        if(!text_buf)
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


char get_nextline(t_list *lst)
{
    char *line;
    int i;
    int j;
    int len;

    len = lst_size(lst);
    line = malloc(len + 1);
    if(!line)
        return(NULL);
    i = 0;
    while(lst)
    {
        j = 0;
        while(lst->content[j] != '\0')
        {
            if(lst->content[j] == '\n')
            {
                line[i++] = '\n';
                line[i] = '\0';
                return(line);
            }
            line[i] = lst->content[j];
            ++i;
            ++j;
        }
        lst = lst->next;
    }
    line[i] = '\0';
    return(line);
}

void clear_list(t_list **lst)
{
    t_list *tmp;

    while(*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->content);
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}

