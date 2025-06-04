/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpazouki <mpazouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:50:29 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/04 00:27:38 by mpazouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

void	free_all_gnl_residuals(void)
{
    extern t_res *res_lst; // Declare the static variable as extern
    t_res *tmp;

    while (res_lst)
    {
        tmp = res_lst->next;
        free(res_lst->res_str);
        free(res_lst);
        res_lst = tmp;
    }
}