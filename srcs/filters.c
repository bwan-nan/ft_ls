/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:41:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 06:42:42 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		file_name_filter(void *data, void *filter)
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

int		file_filter(void *data, void *filter)
{
	t_list		*previous;
	t_list		*current;

	if (!(current = ((t_prgm *)filter)->args))
		return (0);
	if(ft_strequ(((t_status *)data)->name, (char *)(current->data))
			&& !S_ISDIR(((t_status *)(data))->info.st_mode))
	{
		ft_lstpop(&(((t_prgm *)filter)->args), NULL);
		return (1);
	}
	previous = current;
	while ((current = current->next))
	{
		if(ft_strequ(((t_status *)data)->name, (char *)current->data)
				&& !S_ISDIR(((t_status *)data)->info.st_mode))
		{
			ft_lstdelnext(previous, NULL);
			return (1);
		}
		previous = previous->next;
	}
	return (0);
}

int		dir_filter(void *data, void *filter)
{
	t_list		*previous;
	t_list		*current;

	if (!(current = ((t_prgm *)filter)->args))
		return (0);
	if(ft_strequ(((t_status *)data)->name, (char *)current->data)
			&& S_ISDIR(((t_status *)data)->info.st_mode))
	{
		ft_lstpop(&((t_prgm *)filter)->args, NULL);
		return (1);
	}
	previous = current;
	while ((current = current->next))
	{
		if(ft_strequ(((t_status *)data)->name, (char *)current->data)
				&& S_ISDIR(((t_status *)data)->info.st_mode))
		{
			ft_lstdelnext(previous, NULL);
			return (1);
		}
		previous = previous->next;
	}
	return (0);
}

