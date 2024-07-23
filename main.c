/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-07 14:31:50 by mpazouki          #+#    #+#             */
/*   Updated: 2024-07-07 14:31:50 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd = open("test.txt", O_RDONLY | O_CREAT);
    char *line;
    t_list *lst = NULL;

    while ((line = get_next_line(&lst)) != NULL) 
	{
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}