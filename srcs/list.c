/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/01 17:51:48 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	generate_lists(t_prgm *glob, t_list **file, t_list **dir)
{
	t_list		*args;
	t_status	tmp;

	args = glob->args;
	while (args && !(tmp.path = NULL))
	{
		tmp.dirlist = NULL;
		tmp.name = ft_strdup((char *)args->data);
		ft_asprintf(&tmp.path, "%s", (char *)args->data);
		if(lstat(tmp.path, &tmp.info) == 0)
		{
			if (!S_ISDIR(tmp.info.st_mode))
				ft_lstaddback(file, ft_lstnew(&tmp, sizeof(t_status)));
			else if (S_ISDIR(tmp.info.st_mode))
				ft_lstaddback(dir, ft_lstnew(&tmp, sizeof(t_status)));
		}
		else
			error(glob, &tmp);
		args = args->next;
	}
}

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
	file.name = ft_strdup(get_file->d_name);
	ft_asprintf(&file.path, "%s/%s", path, file.name);
	lstat(file.path, &file.info);
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
