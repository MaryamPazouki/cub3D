#include "map_validation.h"


void	ft_free_map(char **map)
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
void free_game(t_game *game)
{
	if (!game)
        return;
	
	ft_free_map(game->map);
    free(game->textures_info.n_wall_path);
    free(game->textures_info.s_wall_path);
    free(game->textures_info.w_wall_path);
    free(game->textures_info.e_wall_path);
	// game->map = NULL;
    // game->textures_info.n_wall_path = NULL;
    // game->textures_info.s_wall_path = NULL;
    // game->textures_info.w_wall_path = NULL;
    // game->textures_info.e_wall_path = NULL;
	// free(game);
	// free_all_gnl_residuals();
}
void	free_all_and_exit(t_game *game, const char *msg, int status)
{
	if (msg)
		fprintf(stderr, "Error: %s\n", msg);
	free_game(game);
	exit(status);
}

void free_tokens(char **tokens)
{
    int i = 0;
    while (tokens && tokens[i])
        free(tokens[i++]);
    free(tokens);
}



int encode_rgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}






// ---------------ft_split_tokens.c----------------

static int	is_sep(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	count_words(const char *str, const char *charset)
{
	int count = 0;

	while (*str)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (*str && !is_sep(*str, charset))
		{
			count++;
			while (*str && !is_sep(*str, charset))
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *str, const char *charset)
{
	int		len = 0;
	char	*word;

	while (str[len] && !is_sep(str[len], charset))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	for (int i = 0; i < len; i++)
		word[i] = str[i];
	word[len] = '\0';
	return (word);
}

char	**ft_split_tokens(const char *str, const char *charset)
{
	int		words = count_words(str, charset);
	char	**result = malloc(sizeof(char *) * (words + 1));
	int		i = 0;

	if (!result || !str)
		return (NULL);
	while (*str)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (*str && !is_sep(*str, charset))
		{
			result[i++] = malloc_word(str, charset);
			while (*str && !is_sep(*str, charset))
				str++;
		}
	}
	result[i] = NULL;
	return (result);
}
