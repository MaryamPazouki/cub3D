#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	int fd;
	char *line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL) 
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}