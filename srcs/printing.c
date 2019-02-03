/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/03 02:08:17 by cedricmpa        ###   ########.fr       */
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

void	basic_padding(t_list *lst, t_display *info)
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

void	print_basic(t_prgm *glob, t_list *lst, t_display *info)
{
	t_status	*tmp;
	char		*col;

	col = NULL;
	tmp = ((t_status *)(lst)->data);
	while (info->total > info->window.ws_col)
		info->total = info->total / 2;
	while (lst)
	{
		tmp = ((t_status *)(lst)->data);
		if (glob->option & LS_G)
			col =  display_color(glob, tmp->info.st_mode);
		info->printed += ft_printf("%@-*s", col ? col : ""
									, info->width, tmp->name);
		if (info->printed > info->total)
		{
			ft_putchar('\n');
			info->printed = 0;
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
		if ((info->printed + 2 + info->size) > info->window.ws_col)
		{
			ft_putchar('\n');
			info->printed = 0;
		}
	}
	else
		info->printed += ft_printf("%r%s%r\n", col ? col : "", tmp->name
											, col ? glob->colors[11] : "");
}

void	print_line(t_prgm *glob, t_status *file, t_display *info)
{
	char	*col;

	col = glob->option & LS_G ? display_color(glob, file->info.st_mode) : NULL;
	info->time = glob->option & LS_TT ? 20 : 12;
	if (S_ISCHR(file->info.st_mode) || S_ISBLK(file->info.st_mode))
	{
		ft_printf("%*s %*d %-*s  %-*s  %*d, %*d %.*s %@s"
				, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
				, info->pw_len, file->pwd , info->gr_len, file->grp
				, info->maj_len, major(file->info.st_rdev), info->min_len
				, minor(file->info.st_rdev), info->time
				, ctime(&file->info.st_mtime) + 4
				, col ? col : "" , file->name);
	}
	else
	{
		ft_printf("%-*s %*d %-*s  %-*s  %*d %.*s %@s"
				, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
				, info->pw_len, file->pwd, info->gr_len, file->grp, info->size
				, file->info.st_size, info->time
				, ctime(&file->info.st_mtime) + 4
				, col ? col : "" , file->name);
	}
	symbolic_link(file);
}
