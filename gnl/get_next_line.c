/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:02:56 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/05 11:35:32 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_free_rd(char *buffer, t_gnl_list **lst)
{
	free (buffer);
	gnl_lstclear(lst, &free);
	return (0);
}

int	ft_read_lst(int fd, t_gnl_list **lst, int temp_rd, int acum)
{
	char	*buffer;

	while (temp_rd)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (0);
		temp_rd = read(fd, buffer, BUFFER_SIZE);
		if (temp_rd == -1)
			return (ft_free_rd(buffer, lst));
		acum += temp_rd;
		if (acum == 0)
		{
			free (buffer);
			return (0);
		}
		*(buffer + temp_rd) = '\0';
		if (gnl_strchr(buffer, '\n'))
			temp_rd = 0;
		ft_lstadd_back_gnl(lst, buffer);
	}
	return (acum);
}

char	*ft_create_residual(char *str, char	**residual, char **line)
{
	int		first;
	int		second;
	char	*temp;

	second = 0;
	first = 0;
	while (*(str + first) && *(str + first) != '\n')
		first++;
	ft_strcpy_len(line, str, first + 1);
	if (*(str + first) == '\n')
		first++;
	while (*(str + first + second))
		second++;
	if (second > 0)
	{
		temp = (char *)malloc((second + 1) * sizeof(char));
		if (!temp)
			return (NULL);
		*temp = '\0';
		ft_strcpy_len(&temp, (str + first), second + 1);
		*residual = temp;
	}
	return (NULL);
}

char	*ft_line_assembly(t_gnl_list **lst, char **residual, int read_n)
{
	char		*line;
	t_gnl_list	*line_lst;

	line_lst = *lst;
	line = (char *)malloc((read_n + 1) * sizeof(char));
	*line = '\0';
	while (line_lst)
	{
		if (gnl_strchr((char *)line_lst->content, '\n'))
			ft_create_residual((char *)line_lst->content, residual, &line);
		else
			ft_strcpy_len(&line, (char *)line_lst->content, BUFFER_SIZE + 1);
		line_lst = line_lst->next;
	}
	gnl_lstclear(lst, &free);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*residual = NULL;
	t_gnl_list		*line_lst;
	int				read_n;

	read_n = 0;
	line_lst = NULL;
	if (residual)
	{
		while (*(residual + read_n))
			read_n++;
		ft_lstadd_back_gnl(&line_lst, residual);
		residual = NULL;
		if (gnl_strchr((char *)line_lst->content, '\n'))
			return (ft_line_assembly(&line_lst, &residual, read_n));
	}
	read_n += ft_read_lst(fd, &line_lst, 1, 0);
	if (!line_lst)
		return (NULL);
	return (ft_line_assembly(&line_lst, &residual, read_n));
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char	*result;

// 	i = 0;
// 	// fd = open("sth.txt", O_RDONLY);
// 	// fd = open("1char.txt", O_RDONLY);
// 	// fd = open("one_line_no_nl.txt", O_RDONLY);
// 	// fd = open("variable_nls.txt", O_RDONLY);
// 	fd = 0;
// 	printf("FD: %d\nBUFFSIZE: %d\n", fd, BUFFER_SIZE);
// 	while (i < 14)
// 	{
// 		result = get_next_line(fd);
// 		printf("result %d: %s\n", i + 1, result);
// 		free(result);
// 		i++;
// 	}

// 	return (0);
// }
