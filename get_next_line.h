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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>

typedef struct s_list
{
	char*			content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int		lst_size(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, char *new_buf);
int		is_newline(t_list *lst);
void	create_list(t_list **lst, int fd);
char	*get_newline(t_list *lst);
void	node_with_nl(t_list **lst);
void	clear_list(t_list **lst, t_list	*nl_node,char	*buf);

#endif
