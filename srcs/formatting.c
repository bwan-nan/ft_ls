/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/26 08:03:10 by cempassi         ###   ########.fr       */
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

void			padding(t_list *lst, size_t *nlink, size_t *size, size_t *total)
{
	t_status	*tmp;
	size_t		len;

	while (lst)
	{
		tmp = (t_status *)(lst->data);
		if ((len = nbrlen(tmp->info.st_nlink)) > *nlink)
			*nlink = len;
		if ((len = nbrlen(tmp->info.st_size)) > *size)
			*size = len;
		*total += tmp->info.st_blocks;
		lst = lst->next;
	}
}

void			line_display(t_status *file, size_t nlink, size_t size)
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
	ft_printf("%s  %*d %s  %s  %*d %.12s %s\n"
			, permissions
			, nlink, file->info.st_nlink
			, (getpwuid(file->info.st_uid))->pw_name
			, (getgrgid(file->info.st_gid))->gr_name
			, size, file->info.st_size
			, ctime(&file->info.st_mtime) + 4
			, file->name);
}
