/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-07 14:18:37 by mpazouki          #+#    #+#             */
/*   Updated: 2024-07-07 14:18:37 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>


typedef struct t_list
{
	char* content;
	struct s_list *next;
}t_list;


char	*get_next_line(int fd);
int 	lst_size(t_list *lst);
void	ft_lstadd_back(t_list **lst, char *new_buf);
int		is_newline(t_list *lst);
void	create_lst(t_list **lst, int fd);
char	get_newline(t_list *lst);
void	clear_lst(t_list **lst);

#endif