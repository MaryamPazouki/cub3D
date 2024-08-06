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
	static t_list *lst = NULL;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_list(&lst, fd);
	if (!lst)
		return (NULL);
	line = get_line(lst);
	node_with_nl(&lst);
	return (line);
}