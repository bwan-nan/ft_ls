/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/06 19:52:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	basic_padding(t_prgm *glob, t_list *lst, t_display *info)
{
	t_list		*tmp;
	size_t		len;
	int			i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if ((len = ft_strlen(((t_status *)tmp->data)->name)) >= info->width)
		{
			info->width = len + 5;
			tmp = lst;
			info->lst_len = 0;
			info->total = 0;
		}
		info->lst_len++;
		tmp = tmp->next;
	}
	while ((info->total += info->width + 1) < glob->window.ws_col)
		if (info->total <= info->lst_len * (info->width + 1))
			i++;
	info->total = i;
	return ;
}

void	print_basic_line(t_prgm *glob, t_list *lst, t_display *info)
{
	t_status	*tmp;
	char		*col;
	size_t		i;

	i = 0;
	while (lst)
	{
		tmp = ((t_status *)(lst)->data);
		if (glob->option & LS_G)
		{
			col = display_color(glob, tmp->info.st_mode);
			info->printed += ft_printf("%@-*s", col, info->width, tmp->name);
		}
		else
			info->printed += ft_printf("%-*s", info->width, tmp->name);
		i++;
		if (i == info->total && lst->next)
		{
			ft_putchar('\n');
			i = 0;
		}
		lst = lst->next;
	}
}

void	print_basic_col(t_prgm *glob, t_list *lst, t_display *info, char *colo)
{
	t_list		*tmp;
	size_t		col;
	size_t		row;
	size_t		elem;

	row = 0;
	while (row < info->lines + info->mod && !(col = 0))
	{
		tmp = lst;
		while (col < info->total && !(elem = 0) && tmp)
		{
			glob->tmp = *(t_status *)tmp->data;
			if (glob->option & LS_G)
				colo = display_color(glob, glob->tmp.info.st_mode);
			ft_printf("%-@*s", colo, info->width, glob->tmp.name);
			while (elem++ < (info->lines + info->mod) && tmp)
				tmp = tmp->next;
			col++;
		}
		if (++row < info->lines + info->mod && (lst = lst->next))
			ft_putchar('\n');
	}
}

void	print_commas(t_prgm *glob, t_list *lst, t_display *info)
{
	t_status	*tmp;
	char		*col;

	tmp = (t_status *)(lst->data);
	col = glob->option & LS_G ? display_color(glob, tmp->info.st_mode) : NULL;
	if (lst->next)
	{
		info->printed += ft_printf("%@s, ", col, tmp->name);
		if ((info->printed + 2 + info->size) > glob->window.ws_col)
		{
			ft_putchar('\n');
			info->printed = 0;
		}
	}
	else
		info->printed += ft_printf("%@s\n", col, tmp->name);
}
