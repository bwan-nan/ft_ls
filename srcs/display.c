/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/24 22:23:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	ft_printf("%s  %*d %s  %s  %*d %.12s %s\n", permissions
			, nlink, file->info.st_nlink
			, (getpwuid(file->info.st_uid))->pw_name
			, (getgrgid(file->info.st_gid))->gr_name
			, size, file->info.st_size
			, ctime(&file->info.st_mtime) + 4
			, file->name);
}

void			long_output(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	size_t		nlink_max;
	size_t		size_max;
	size_t		total;

	nlink_max = 0;
	size_max = 0;
	total = 0;
	padding(files_list, &nlink_max, &size_max, &total);
	tmp = (t_status *)(files_list->data);
	if (!ft_strequ(glob->dir, ".") && glob->option & LS_RR)
		ft_printf("%s\n", glob->dir);
	ft_printf("total %d\n", total);
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		line_display(tmp, nlink_max, size_max);
		files_list = files_list->next;
	}
}
