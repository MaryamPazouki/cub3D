/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-05 07:45:11 by mpazouki          #+#    #+#             */
/*   Updated: 2024-07-05 07:45:11 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list *lst;
	char next_line;

	lst = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &lst, 0) < 0)
		return (NULL);

	// create a list till we get the \n
	create_lst(&lst, fd);
	if(!lst)
		return(NULL);


	next_line = get_newline(lst);

	clear_lst(&lst);

	return (next_line);
}

