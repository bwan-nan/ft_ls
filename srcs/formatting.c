/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/07 13:13:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>
#include <unistd.h>

size_t	nbrlen(int nbr)
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

void	init_display(t_display *info)
{
	info->width = 10;
	info->total = 0;
	info->lines = 0;
	info->lst_len = 0;
	info->printed = 0;
	info->nlink = 0;
	info->size = 0;
	info->pw_len = 0;
	info->gr_len = 0;
	info->maj_len = 0;
	info->min_len = 0;
	info->ch_len = 0;
}

void	symbolic_link(t_status *file)
{
	char	buf[DIR_MAX];

	if (ft_strequ(file->name, "stderr"))
		ft_putstr("-> fd/2");
	else if (ft_strequ(file->name, "stdin"))
		ft_putstr("-> fd/0");
	else if (ft_strequ(file->name, "stdout"))
		ft_putstr("-> fd/1");
	else if (S_ISLNK(file->info.st_mode))
	{
		readlink(file->path, buf, file->info.st_size);
		buf[file->info.st_size] = '\0';
		ft_printf(" -> %*s", file->info.st_size, buf);
	}
}

char	*str_chmod(t_status *file, char *buffer)
{
	char	p[12];

	file->xattr_len = listxattr(file->path, buffer, DIR_MAX, XATTR_NOFOLLOW);
	file->acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	p[0] = '\0';
	p[0] = !*p && S_ISREG(file->info.st_mode) ? '-' : *p;
	p[0] = !*p && S_ISDIR(file->info.st_mode) ? 'd' : *p;
	p[0] = !*p && S_ISCHR(file->info.st_mode) ? 'c' : *p;
	p[0] = !*p && S_ISBLK(file->info.st_mode) ? 'b' : *p;
	p[0] = !*p && S_ISLNK(file->info.st_mode) ? 'l' : *p;
	p[0] = !*p && S_ISFIFO(file->info.st_mode) ? 'f' : *p;
	p[0] = !*p ? 's' : *p;
	p[1] = file->info.st_mode & S_IRUSR ? 'r' : '-';
	p[2] = file->info.st_mode & S_IWUSR ? 'w' : '-';
	p[3] = file->info.st_mode & S_IXUSR ? 'x' : '-';
	p[4] = file->info.st_mode & S_IRGRP ? 'r' : '-';
	p[5] = file->info.st_mode & S_IWGRP ? 'w' : '-';
	p[6] = file->info.st_mode & S_IXGRP ? 'x' : '-';
	p[7] = file->info.st_mode & S_IROTH ? 'r' : '-';
	p[8] = file->info.st_mode & S_IWOTH ? 'w' : '-';
	p[9] = file->info.st_mode & S_IXOTH ? 'x' : '-';
	p[10] = file->acl ? '+' : ' ';
	p[10] = file->xattr_len > 0 ? '@' : p[10];
	p[11] = '\0';
	return (ft_strdup(p));
}

void	output_handler(t_prgm *glob, t_list *lst)
{
	if (lst)
	{
		if (glob->option & LS_L || glob->option & LS_AR)
			long_output(glob, lst);
		else if (glob->option & LS_1)
			list_output(glob, lst);
		else if (glob->option & LS_M)
			commas_output(glob, lst);
		else
			basic_output(glob, lst);
	}
}
