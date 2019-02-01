/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 17:41:08 by bwan-nan         ###   ########.fr       */
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
		if (S_ISCHR(tmp->info.st_mode))
			i->dev_on = 1;
		if ((len = nbrlen(tmp->info.st_nlink)) > i->nlink)
			i->nlink = len;
		if ((len = ft_strlen(getpwuid(tmp->info.st_uid)->pw_name)) > i->pw_len)
			i->pw_len = len;
		if ((len = ft_strlen(getgrgid(tmp->info.st_gid)->gr_name)) > i->gr_len)
			i->gr_len = len;
		if (i->dev_on)
		{
			if ((len = nbrlen(major(tmp->info.st_rdev))) > i->maj_len)
				i->maj_len = len;
			if ((len = nbrlen(minor(tmp->info.st_rdev))) > i->min_len)
				i->min_len = len;
			i->size = i->min_len + i->maj_len + 5;
		}
		else if ((len = nbrlen(tmp->info.st_size)) > i->size)
			i->size = len;
		i->total += tmp->info.st_blocks;
		lst = lst->next;
	}
}

static void		symbolic_link(t_status *file, char *chmod)
{
	char	buf[DIR_MAX];

	if (*chmod == 'l')
	{
		readlink(file->path, buf, file->info.st_size);
		buf[file->info.st_size] = '\0';
		ft_printf(" -> %*s", file->info.st_size, buf);
	}
}

void				device_num(t_status *file, t_display *info, char *chmod)
{
	if (*chmod == 'b' || *chmod == 'c')
		ft_printf("  %*d,  %*d"\
			   	, info->maj_len, major(file->info.st_rdev)\
			 	, info->min_len, minor(file->info.st_rdev));   
}

void			line_display(t_prgm *glob, t_status *file, t_display *info)
{
	char	chmod[11];

	chmod[0] = get_file_type(file->info.st_mode);
	chmod[1] = file->info.st_mode & S_IRUSR ? 'r' : '-';
	chmod[2] = file->info.st_mode & S_IWUSR ? 'w' : '-';
	chmod[3] = file->info.st_mode & S_IXUSR ? 'x' : '-';
	chmod[4] = file->info.st_mode & S_IRGRP ? 'r' : '-';
	chmod[5] = file->info.st_mode & S_IWGRP ? 'w' : '-';
	chmod[6] = file->info.st_mode & S_IXGRP ? 'x' : '-';
	chmod[7] = file->info.st_mode & S_IROTH ? 'r' : '-';
	chmod[8] = file->info.st_mode & S_IWOTH ? 'w' : '-';
	chmod[9] = file->info.st_mode & S_IXOTH ? 'x' : '-';
	chmod[10] = '\0';
	ft_printf("%s  %-*d %-*s  %-*s "\
			, chmod
			, info->nlink, file->info.st_nlink\
			, info->pw_len, (getpwuid(file->info.st_uid))->pw_name\
			, info->gr_len, (getgrgid(file->info.st_gid))->gr_name);
	chmod[0] == 'c' || chmod[0] == 'b' ? device_num(file, info, chmod) :\
	ft_printf("%*d", info->size, file->info.st_size);
	ft_printf(" %.*s %s"
			, glob->option & LS_TT ? 20 : 12, ctime(&file->info.st_mtime) + 4\
			, file->name);\
	symbolic_link(file, chmod);
	ft_putchar('\n');
}
