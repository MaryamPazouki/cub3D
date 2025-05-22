#include "main_header.h"

void	print_map(char **map)
{
	int i = 0;

	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
