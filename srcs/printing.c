/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 18:18:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_padding(t_list *lst, t_display *i)
{
	t_status	*tmp;
	size_t		len;

	while (lst)
	{
		tmp = (t_status *)(lst->data);
		if ((len = nbrlen(tmp->info.st_nlink)) > i->nlink)
			i->nlink = len;
		if ((len = nbrlen(tmp->info.st_size)) > i->size)
			i->size = len;
		if ((len = ft_strlen(getpwuid(tmp->info.st_uid)->pw_name)) > i->pw_len)
			i->pw_len = len;
		if ((len = ft_strlen(getgrgid(tmp->info.st_gid)->gr_name)) > i->gr_len)
			i->gr_len = len;
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

void	print_comma(t_list *files_list, t_display *info)
{
	t_status	*tmp;
	size_t		len;

	len = 0;
	tmp = (t_status *)(files_list->data);
	if (files_list->next)
	{
		info->printed += ft_printf("%s, ", tmp->name);
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
	char	permissions[11];

	permissions[0] = get_file_type(file->info.st_mode);
	permissions[1] = file->info.st_mode & S_IRUSR ? 'r' : '-';
	permissions[2] = file->info.st_mode & S_IWUSR ? 'w' : '-';
	permissions[3] = file->info.st_mode & S_IXUSR ? 'x' : '-';
	permissions[4] = file->info.st_mode & S_IRGRP ? 'r' : '-';
	permissions[5] = file->info.st_mode & S_IWGRP ? 'w' : '-';
	permissions[6] = file->info.st_mode & S_IXGRP ? 'x' : '-';
	permissions[7] = file->info.st_mode & S_IROTH ? 'r' : '-';
	permissions[8] = file->info.st_mode & S_IWOTH ? 'w' : '-';
	permissions[9] = file->info.st_mode & S_IXOTH ? 'x' : '-';
	permissions[10] = '\0';
	ft_printf("%s  %-*d %-*s  %-*s  %*d %.*s %s\n"
			, permissions
			, info->nlink, file->info.st_nlink
			, info->pw_len, (getpwuid(file->info.st_uid))->pw_name
			, info->gr_len, (getgrgid(file->info.st_gid))->gr_name
			, info->size, file->info.st_size
			, glob->option & LS_TT ? 20 : 12, ctime(&file->info.st_mtime) + 4
			, file->name);
	symbolic_link(file, permissions);
}
