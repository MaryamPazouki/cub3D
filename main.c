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
	line = get_next_line(fd);
	if (line != NULL) 
	{
    	printf("%s\n", line);
    	free(line);
	} else 
	{
    	printf("get_next_line returned NULL.\n");
	}
	close(fd);
	return (0);
}