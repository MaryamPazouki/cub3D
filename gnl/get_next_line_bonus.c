/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:02:56 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/05 11:35:32 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		{
			free (buffer);
			return (gnl_lstclear(lst, &free));
		}
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

	if ((*lst) == NULL)
		return (NULL);
	line_lst = *lst;
	line = (char *)malloc((read_n + 1) * sizeof(char));
	if (!line)
		return (NULL);
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

char	**ft_find_residual(int fd, t_res **res_lst)
{
	t_res	*temp_lst;
	t_res	*new_res;

	temp_lst = *res_lst;
	while (temp_lst)
	{
		if (temp_lst->fd == fd)
			return ((char **)&(temp_lst->res_str));
		new_res = temp_lst;
		temp_lst = temp_lst->next;
	}
	temp_lst = new_res;
	new_res = (t_res *)malloc(sizeof(t_res));
	if (!new_res)
		return (NULL);
	new_res->next = NULL;
	new_res->fd = fd;
	new_res->res_str = NULL;
	if (!(*res_lst))
		*res_lst = new_res;
	else
		temp_lst->next = new_res;
	return ((char **)&((new_res)->res_str));
}

char	*get_next_line(int fd)
{
	static t_res	*res_lst;
	char			**residual;
	t_gnl_list		*line_lst;
	int				read_n;
	char			*ret;

	if (fd < 0)
		return (NULL);
	residual = (char **)ft_find_residual(fd, &res_lst);
	read_n = 0;
	line_lst = NULL;
	if (*residual)
	{
		while (*(*residual + read_n))
			read_n++;
		ft_lstadd_back_gnl(&line_lst, *residual);
		*residual = NULL;
		if (gnl_strchr((char *)line_lst->content, '\n'))
			return (ft_line_assembly(&line_lst, residual, read_n));
	}
	read_n += ft_read_lst(fd, &line_lst, 1, 0);
	ret = ft_line_assembly(&line_lst, residual, read_n);
	if (!(*residual))
		ft_del_node(fd, &res_lst);
	return (ret);
}

// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char	*result;

// 	i = 0;
// 	// fd = open("sth.txt", O_RDONLY);
// 	// fd = open("1char.txt", O_RDONLY);
// 	// fd = open("one_line_no_nl.txt", O_RDONLY);
// 	fd = open("variable_nls.txt", O_RDONLY);
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
