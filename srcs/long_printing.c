/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_printing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 22:08:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/13 20:47:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

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

void	time_format(t_prgm *glob, t_display *info, time_t timestamp)
{
	time_t		today;

	time(&today);
	if (glob->option & LS_TT)
	{
		info->time = 20;
		info->time2 = 0;
	}
	else if (today - timestamp > SIX_MONTHS || timestamp 
			- today > 0)
	{
		info->time = 6;
		info->time2 = 4;
	}
	else
	{
		info->time = 12;
		info->time2 = 0;
	}
}

void	print_long_device(t_prgm *glob, t_status *file, t_display *info)
{
	char	*full_date;
	char	*col;

	col = glob->option & LS_G ? display_color(glob, file->info.st_mode) : NULL;
	full_date = ft_strdup(ctime(&file->info.st_mtime));
	ft_printf("%*s %*d %-*s  %-*s  %*ld, %*d %.*s %.*s%.*s%.*s %@s"
			, info->ch_len, file->chmod
			, info->nlink, file->info.st_nlink
			, info->pw_len, file->pwd
			, info->gr_len, file->grp
			, info->maj_len, major(file->info.st_rdev)
			, info->min_len, minor(file->info.st_rdev)
			, info->time2 ? 1 : 0, " "
			, info->time, full_date + 4
			, info->time2, full_date + 20
			, info->time2 ? 1 : 0, " "
			, col, file->name);
	ft_strdel(&full_date);
}

void	print_long_regular(t_prgm *glob, t_status *file, t_display *info)
{
	char	*full_date;
	char	*col;

	col = glob->option & LS_G ? display_color(glob, file->info.st_mode) : NULL;
	full_date = ft_strdup(ctime(&file->info.st_mtime));
	ft_printf("%-*s %*d %-*s  %-*s  %*ld %.*s %.*s%.*s%.*s%@s"
			, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
			, info->pw_len, file->pwd ? file->pwd : ""
			, info->gr_len, file->grp ? file->grp : ""
			, info->size, file->info.st_size
			, info->time, full_date + 4
			, info->time2 ? 1 : 0, " "
			, info->time2, full_date + 20
			, info->time2 ? 1 : 0, " "
			, col, file->name);
	ft_strdel(&full_date);
}

void	print_line(t_prgm *glob, t_status *file, t_display *info)
{
	time_format(glob, info, file->info.st_mtime);
	if (S_ISCHR(file->info.st_mode) || S_ISBLK(file->info.st_mode))
		print_long_device(glob, file, info);
	else
		print_long_regular(glob, file, info);
	symbolic_link(file);
	if (file->xattr && glob->option & LS_AR)
		print_xattr(file, file->xattr);
	if (file->acl && glob->option & LS_E)
		print_acl(file);
}
