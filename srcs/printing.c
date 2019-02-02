/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/02 19:28:40 by bwan-nan         ###   ########.fr       */
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
		if ((len = ft_strlen(getpwuid(tmp->info.st_uid)->pw_name)) > i->pw_len)
			i->pw_len = len;
		if ((len = ft_strlen(getgrgid(tmp->info.st_gid)->gr_name)) > i->gr_len)
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

void	print_basic(t_list *lst, t_display *info)
{
	t_status	*tmp;

	while (info->total > info->window.ws_col)
		info->total = info->total / 2;
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

void	print_commas(t_prgm *glob, t_list *files_list, t_display *info)
{
	t_status	*tmp;
	size_t		len;
	size_t		color_len;

	len = 0;
	tmp = (t_status *)(files_list->data);
	get_color(glob, tmp);
	color_len = ft_strlen(glob->color) + 6;
	if (files_list->next)
	{
		info->printed += ft_printf("%s%s, ", glob->color, tmp->name) - color_len;
		if (info->printed + 2 + info->size > info->window.ws_col)
		{
			ft_putchar('\n');
			info->printed = 0;
		}
	}
	else
		info->printed += ft_printf("%s\n", tmp->name);
}

void	print_line(t_prgm *glob, t_status *file, t_display *info)
{
	get_color(glob, file);
	info->time = glob->option & LS_TT ? 20 : 12;
	if (S_ISCHR(file->info.st_mode) || S_ISBLK(file->info.st_mode))
	{
		ft_printf("%*s  %-*d %-*s  %-*s  %*d, %*d %.*s %s%s\033[0m"
				, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
				, info->pw_len, (getpwuid(file->info.st_uid))->pw_name
				, info->gr_len, (getgrgid(file->info.st_gid))->gr_name
				, info->maj_len, major(file->info.st_rdev)
				, info->min_len, minor(file->info.st_rdev)
				, info->time, ctime(&file->info.st_mtime) + 4
				, glob->color, file->name);
	}
	else
	{
		ft_printf("%-*s  %-*d %-*s  %-*s  %*d %.*s %s%s\033[0m"
				, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
				, info->pw_len, (getpwuid(file->info.st_uid))->pw_name
				, info->gr_len, (getgrgid(file->info.st_gid))->gr_name
				, info->size, file->info.st_size
				, info->time, ctime(&file->info.st_mtime) + 4
				, glob->color, file->name);
	}
	symbolic_link(file);
}
