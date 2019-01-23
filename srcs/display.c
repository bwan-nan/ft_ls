/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/21 18:58:02 by bwan-nan         ###   ########.fr       */
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

static void		display_permissions(int mode)
{
	char	permissions[11];

	permissions[0] = get_file_type(mode);
	permissions[1] = mode & S_IRUSR ? 'r' : '-';
	permissions[2] = mode & S_IWUSR ? 'w' : '-';
	permissions[3] = mode & S_IXUSR ? 'x' : '-';
	permissions[4] = mode & S_IRGRP ? 'r' : '-';
	permissions[5] = mode & S_IWGRP ? 'w' : '-';
	permissions[6] = mode & S_IXGRP ? 'x' : '-';
	permissions[7] = mode & S_IROTH ? 'r' : '-';
	permissions[8] = mode & S_IWOTH ? 'w' : '-';
	permissions[9] = mode & S_IXOTH ? 'x' : '-';
	permissions[10] = '\0';
	ft_printf("%s ", permissions);
}

static void		display_time(time_t last_modification)
{
	char	*full_date;

	full_date = ctime(&last_modification) + 4;
	ft_printf("%.12s ", full_date);
}

void			display_working_directory(char *path)
{
	char	*working_directory;

	working_directory = ft_strsub(path, 0, ft_strlen(path) - 2);
	ft_printf("%s\n", working_directory);
	ft_strdel(&working_directory);
}

void			print_list(t_list *files_list)
{
	t_status	*tmp;
	int			size[3];

	get_the_right_size(files_list, size);
	tmp = (t_status *)(files_list->data);
	if (!ft_strequ(tmp->path, "./."))
		display_working_directory(tmp->path);
	ft_printf("total %d\n", size[2]);
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		display_permissions(tmp->info.st_mode);
		ft_printf("%*d ", size[0], tmp->info.st_nlink);
		ft_printf("%s ", (getpwuid(tmp->info.st_uid))->pw_name);
		ft_printf("%s ", (getgrgid(tmp->info.st_gid))->gr_name);
		ft_printf("%*d ", size[1], tmp->info.st_size);
		display_time(tmp->info.st_mtime);
		ft_printf("%s\n", tmp->dirent->d_name);
		files_list = files_list->next;
	}
	ft_putchar('\n');
}
