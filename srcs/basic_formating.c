/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 07:35:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 09:26:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		basic_padding(t_list *lst, t_display *info)
{
	t_list		*tmp;
	size_t		len;

	ioctl(0, TIOCGWINSZ, &info->window);
	tmp = lst;
	while (tmp)
	{
		if ((len = ft_strlen(((t_status *)tmp->data)->name)) > info->width)
		{
			info->width = len + 5;
			tmp = lst;
			info->total = 0;
			continue;
		}
		tmp = tmp->next;
		info->total += info->width;
	}
	return ;
}

void		basic_default(t_prgm *glob, t_list *lst, t_display *info)
{
	t_status 	*tmp;

	if(glob->args)
		;
	while (info->total > info->window.ws_col)
		info->total =  info->total / 2;
	if (lst)
		;
	while (lst)
	{
		tmp = ((t_status *)(lst)->data);
		info->printed += ft_printf("%-*s", info->width, tmp->name);
		if (info->printed > info->total)
		{
			ft_putchar('\n');
			info->printed = 0;
		}
		lst = lst->next;
	}
}
