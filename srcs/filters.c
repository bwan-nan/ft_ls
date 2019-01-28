/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:41:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/28 14:06:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_args(t_list *node)
{
	ft_printf("Print args : %s\n", (char *)node->data);
}

int		args_name_filter(void *data, void *filter)
{
	if (ft_strequ(((t_status *)data)->name, (char *)filter))
		return (S_ISDIR(((t_status *)(data))->info.st_mode) ? 0 : 1);
	return (0);
}

int		dir_name_filter(void *data, void *filter)
{
	if (ft_strequ(((char *)data), (char *)filter))
		return (S_ISDIR(((t_status *)(data))->info.st_mode) ? 1 : 0);
	return (0);
}

int		name_filter(void *data, void *filter)
{
	if (ft_strequ((char *)data, ((t_status *)filter)->name))
	{
		ft_printf("filter = :%s\n",((t_status *)filter)->name);
		return (S_ISDIR(((t_status *)(filter))->info.st_mode) ? 0 : 1);
	}
	return (0);
}

int		file_filter(void *data, void *filter)
{
	t_prgm *glob;
	int		result;

	if (!(((t_prgm *)filter)->args))
		return (0);
	glob = (t_prgm *)filter;
	result = ft_lstremove_if(&((t_prgm *)filter)->args, data, name_filter, NULL);
	return (result);
}

int		dir_filter(void *data, void *filter)
{
	if (!((t_prgm *)filter)->args)
		return (0);
	return (ft_lstremove_if(&((t_prgm *)filter)->args,\
				((t_status *)data)->name, dir_name_filter, NULL));
}
