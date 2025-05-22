#include "map_validation.h"

void	free_map(char **map)
{
	int i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
