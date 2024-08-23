#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>


int main (void)
{
	int fd1;
	int fd2;
	int fd3;

	fd1 = open ("test.txt", O_RDWR);
	fd2 = open ("test2.txt", O_RDWR);
	fd3 = open ("test3.txt", O_RDWR);
	char *line;
	while ((line = get_next_line(fd1)) != NULL)
		{
			printf("1\t%s", line);
			free(line);
			line = get_next_line(fd2);
			printf("2\t%s", line);
			free(line);
			line = get_next_line(fd3);
			printf("3\t%s", line);
			free(line);
		}
	// if (line == NULL)
	// 	printf("Helllou\n");
	close (fd1);
	close (fd2);
	close (fd3);
	return 0;
}