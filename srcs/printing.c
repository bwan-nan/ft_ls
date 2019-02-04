/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/04 15:52:33 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_padding(t_list *lst, t_display *i, t_status *tmp, size_t len)
{
	while (lst && (tmp = (t_status *)(lst->data)))
	{
		if ((len = ft_strlen(tmp->chmod)) > i->ch_len)
			i->ch_len = len;
		if ((len = nbrlen(tmp->info.st_nlink)) > i->nlink)
			i->nlink = len;
		if ((len = ft_strlen(tmp->pwd)) > i->pw_len)
			i->pw_len = len;
		if ((len = ft_strlen(tmp->grp)) > i->gr_len)
			i->gr_len = len;
		if (S_ISCHR(tmp->info.st_mode))
		{
			if ((len = nbrlen(major(tmp->info.st_rdev))) > i->maj_len)
				i->maj_len = len;
			if ((len = nbrlen(minor(tmp->info.st_rdev))) > i->min_len)
				i->min_len = len;
			i->size = i->min_len + i->maj_len + 2;
		}
		else if ((len = nbrlen(tmp->info.st_size)) > i->size)
			i->size = len;
		i->total += tmp->info.st_blocks;
		lst = lst->next;
	}
}

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
			info->total = 0;
		}
		tmp = tmp->next;
	}
	while ((info->total += info->width) < glob->window.ws_col)
		i++;
	info->total = i;
	return ;
}

void	print_basic(t_prgm *glob, t_list *lst, t_display *info)
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
			col =  display_color(glob, tmp->info.st_mode);
			info->printed += ft_printf("%@-*s", col , info->width, tmp->name);
		}
		else
			info->printed += ft_printf("%-*s", info->width, tmp->name);
		i++;
		if (i == info->total)
		{
			ft_putchar('\n');
			i = 0;
		}
		lst = lst->next;
	}
}

void	print_commas(t_prgm *glob, t_list *lst, t_display *info)
{
	t_status	*tmp;
	size_t		len;
	char		*col;

	len = 0;
	tmp = (t_status *)(lst->data);
	col = glob->option & LS_G ? display_color(glob, tmp->info.st_mode) : NULL;
	if (lst->next)
	{
		info->printed += ft_printf("%@s, ", col ? col : "", tmp->name);
		if ((info->printed + 2 + info->size) > glob->window.ws_col)
		{
			ft_putchar('\n');
			info->printed = 0;
		}
	}
	else
		info->printed += ft_printf("%@s\n", col ? col : "", tmp->name);
}

void	print_line(t_prgm *glob, t_status *file, t_display *info)
{
	time_format(glob, info, file->info.st_mtime);
	if (S_ISCHR(file->info.st_mode) || S_ISBLK(file->info.st_mode))
		print_device_line(glob, file, info);
	else
		print_regular_line(glob, file, info);
	symbolic_link(file);
}
