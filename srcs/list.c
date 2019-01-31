/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/31 14:18:41 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
static char	*linkname(t_status *file)
{
	char	*link_path;

	link_path = ft_strnew(file->info.st_size);
	readlink(file->path, link_path, file->info.st_size);
	ft_asprintf(&file->name, "", );
}
*/
int		create_list(DIR *current, char *path, t_list **files_list, t_prgm *glob)
{
	t_status	file;
	t_dirent	*get_file;

	if (!(get_file = readdir(current)))
		return (1);
	if (!(glob->option & LS_A) && get_file->d_name[0] == '.')
		return (create_list(current, path, files_list, glob));
	file.path = NULL;
	file.dirlist = NULL;
	file.name = NULL;
	ft_asprintf(&file.path, "%s/%s", path, get_file->d_name);
	lstat(file.path, &file.info);
/*	if (LS_L & glob->option && S_ISLNK(file.info.st_mode))
		file.name = linkname(&file);
	else*/
	file.name = ft_strdup(get_file->d_name);
	ft_lstaddback(files_list, ft_lstnew(&file, sizeof(t_status)));
	return (create_list(current, path, files_list, glob));
}

void	del_node(void **data)
{
	t_status *tmp;

	if (!data || !*data)
		return ;
	tmp = (t_status *)(*data);
	if (tmp->path)
		ft_strdel(&tmp->path);
	if (tmp->name)
		ft_strdel(&tmp->name);
}
