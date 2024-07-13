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

create_list()

get_newline(fd, buf, line)

polish_line(line)



int lst_size(t_list lst)
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


void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}