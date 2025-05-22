/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:49:26 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/02/05 11:35:32 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9
# endif

typedef struct s_gnl_list
{
	void				*content;
	struct s_gnl_list	*next;
}	t_gnl_list;

typedef struct s_res
{
	int				fd;
	char			*res_str;
	struct s_res	*next;
}	t_res;

void	ft_del_node(int fd, t_res **lst);
void	ft_lstadd_back_gnl(t_gnl_list **lst, void *data);
int		gnl_lstclear(t_gnl_list **lst, void (*del)(void *));
char	*gnl_strchr(const char *s, int c);
int		ft_strcpy_len(char **dst, char *src, int len);
char	*ft_line_assembly(t_gnl_list **lst, char **residual, int read_n);
int		ft_read_lst(int fd, t_gnl_list **lst, int temp_rd, int acum);
char	*ft_create_residual(char *str, char	**residual, char **line);
char	*get_next_line(int fd);
int		ft_free_rd(char *buffer, t_gnl_list **lst);
#endif
