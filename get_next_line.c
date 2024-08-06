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

static char *extract_line(t_list **lst)
{
	char *line;
	// check if there is a newline in the list
	line = get_newline(*lst);
	node_with_nl(lst);
	return (line);
}

char *get_next_line(int fd)
{
	static t_list *lst;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	create_list(&lst, fd);
	if (!lst)
		return (NULL);
	line = extract_line(&lst);
	if (!line)
	{
		clear_list(&lst, NULL, NULL);
		return (NULL);
	}
	return (line);
}