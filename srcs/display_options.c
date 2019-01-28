/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:01:52 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/28 19:41:01 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** option -m list files separated by commas
*/

void		list_with_commas(t_list *files_list)
{
	t_status	*tmp;

	if (files_list)
	{
		while (files_list)
		{
			tmp = (t_status *)(files_list->data);
			files_list->next ? ft_printf("%s, ", tmp->name)
				: ft_printf("%s\n", tmp->name);
			files_list = files_list->next;
		}
	}
}
