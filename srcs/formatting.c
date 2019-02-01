/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 13:18:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	nbrlen(int nbr)
{
	if (nbr >= 1000000000)
		return (10);
	if (nbr >= 100000000)
		return (9);
	if (nbr >= 10000000)
		return (8);
	if (nbr >= 1000000)
		return (7);
	if (nbr >= 100000)
		return (6);
	if (nbr >= 10000)
		return (5);
	if (nbr >= 1000)
		return (4);
	if (nbr >= 100)
		return (3);
	if (nbr >= 10)
		return (2);
	return (1);
}

static char		get_file_type(int mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('f');
	else if (S_ISLNK(mode))
		return ('l');
	else
		return ('s');
}

void			padding(t_list *lst, t_display *i)
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

static void		symbolic_link(t_status *file, char *permissions)
{
	char	buf[DIR_MAX];

	if (*permissions == 'l')
	{
		readlink(file->path, buf, file->info.st_size);
		buf[file->info.st_size] = '\0';
		ft_printf(" -> %*s", file->info.st_size, buf);
	}
}

void			line_display(t_prgm *glob, t_status *file, t_display *info)
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
	ft_printf("%s  %-*d %-*s  %-*s  %*d %.*s %s"
			, permissions
			, info->nlink, file->info.st_nlink
			, info->pw_len, (getpwuid(file->info.st_uid))->pw_name
			, info->gr_len, (getgrgid(file->info.st_gid))->gr_name
			, info->size, file->info.st_size
			, glob->option & LS_TT ? 20 : 12, ctime(&file->info.st_mtime) + 4
			, file->name);
	symbolic_link(file, permissions);
	ft_putchar('\n');
}
