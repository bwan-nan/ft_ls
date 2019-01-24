/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 12:19:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		create_list(DIR *current, char *path, t_list **files_list)
{
	t_status	file;
	t_dirent	*get_file;

	if (!(get_file = readdir(current)))
		return (1);
	file.path = NULL;
	file.dirlist = NULL;
	file.name = ft_strdup(get_file->d_name);
	file.inode = get_file->d_ino;
	ft_asprintf(&file.path, "%s/%s", path, file.name);
	stat(file.path, &file.info);
	ft_lstaddback(files_list, ft_lstnew(&file, sizeof(t_status)));
	return (create_list(current, path, files_list));
}

void	del_node(void **data)
{
	t_status *tmp;

	tmp = (t_status *)(*data);
	ft_strdel(&tmp->path);
	ft_strdel(&tmp->name);
}
