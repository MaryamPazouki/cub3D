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
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    char *text = "Hello, world!\n";

    // Open the file for writing (create it if it doesn't exist)
    fd = open("example.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    char *line;
    t_list *lst = NULL;
	line = get_next_line(fd);

    while (line != NULL) 
	{
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}