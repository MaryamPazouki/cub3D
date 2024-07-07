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

char *line;
char *buf;

if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	return (NULL);

buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
if (!buf)
	return(NULL);

// create a list till we get the \n
create_list();

get_newline(fd, buf, line);

polish_line(line);

return (line);
}