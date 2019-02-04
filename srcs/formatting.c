/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/04 21:12:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>

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

char	*getchmod(t_status *file)
{
	char	perm[12];

	perm[0] = '\0';
	perm[0] = !*perm && S_ISREG(file->info.st_mode) ? '-' : *perm;
	perm[0] = !*perm && S_ISDIR(file->info.st_mode) ? 'd' : *perm;
	perm[0] = !*perm && S_ISCHR(file->info.st_mode) ? 'c' : *perm;
	perm[0] = !*perm && S_ISBLK(file->info.st_mode) ? 'b' : *perm;
	perm[0] = !*perm && S_ISLNK(file->info.st_mode) ? 'l' : *perm;
	perm[0] = !*perm && S_ISFIFO(file->info.st_mode) ? 'f' : *perm;
	perm[0] = !*perm ? 's' : *perm;
	perm[1] = file->info.st_mode & S_IRUSR ? 'r' : '-';
	perm[2] = file->info.st_mode & S_IWUSR ? 'w' : '-';
	perm[3] = file->info.st_mode & S_IXUSR ? 'x' : '-';
	perm[4] = file->info.st_mode & S_IRGRP ? 'r' : '-';
	perm[5] = file->info.st_mode & S_IWGRP ? 'w' : '-';
	perm[6] = file->info.st_mode & S_IXGRP ? 'x' : '-';
	perm[7] = file->info.st_mode & S_IROTH ? 'r' : '-';
	perm[8] = file->info.st_mode & S_IWOTH ? 'w' : '-';
	perm[9] = file->info.st_mode & S_IXOTH ? 'x' : '-';
	perm[10] = acl_get_link_np(file->path, ACL_TYPE_EXTENDED) ? '+' : '\0';
	perm[10] = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) ? '@' : perm[10];
	perm[11] = '\0';
	return (ft_strdup(perm));
}

void	output_handler(t_prgm *glob, t_list *lst)
{
	if (lst)
	{
		if (glob->option & LS_L)
			long_output(glob, lst);
		else if (glob->option & LS_1)
			list_output(glob, lst);
		else if (glob->option & LS_M)
			commas_output(glob, lst);
		else
			basic_output(glob, lst);
	}
}
