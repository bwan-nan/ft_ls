/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:21:04 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/30 15:13:41 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_list(t_list **files_list, t_prgm *glob)
{
	if (glob->option & LS_S)
		merge_sort(files_list, &sort_by_size);
	else if (glob->option & LS_T)
		merge_sort(files_list, &sort_time_modified);
/*	else if (glob->option & LS_U)
		merge_sort(files_list, &sort_last_access);*/
	else
		merge_sort(files_list, &sort_ascii);
	if (glob->option & LS_R)
		ft_lstrev(files_list);
}
