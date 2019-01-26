/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 05:49:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		file_name_filter(void *data, void *filter)
{
	if (ft_strequ(((t_status *)data)->name, (char *)filter))
		return (S_ISDIR(((t_status *)(data))->info.st_mode) ? 0 : 1);
	return (0);
}


int		dir_name_filter(void *data, void *filter)
{
	if (ft_strequ(((char *)data), (char *)filter))
		return (S_ISDIR(((t_status *)(data))->info.st_mode) ? 1 : 0);
	return (0);
}

int		file_filter(void *data, void *filter)
{
	t_list		*previous;
	t_list		*current;

	if (!(current = ((t_prgm *)filter)->args))
		return (0);
	if(ft_strequ(((t_status *)data)->name, (char *)(current->data))
			&& !S_ISDIR(((t_status *)(data))->info.st_mode))
	{
		ft_lstpop(&(((t_prgm *)filter)->args), NULL);
		return (1);
	}
	previous = current;
	while ((current = current->next))
	{
		if(ft_strequ(((t_status *)data)->name, (char *)current->data)
				&& !S_ISDIR(((t_status *)data)->info.st_mode))
		{
			ft_lstdelnext(previous, NULL);
			return (1);
		}
		previous = previous->next;
	}
	return (0);
}

int		dir_filter(void *data, void *filter)
{
	t_list		*previous;
	t_list		*current;

	if (!(current = ((t_prgm *)filter)->args))
		return (0);
	if(ft_strequ(((t_status *)data)->name, (char *)current->data)
			&& S_ISDIR(((t_status *)data)->info.st_mode))
	{
		ft_lstpop(&((t_prgm *)filter)->args, NULL);
		return (1);
	}
	previous = current;
	while ((current = current->next))
	{
		if(ft_strequ(((t_status *)data)->name, (char *)current->data)
				&& S_ISDIR(((t_status *)data)->info.st_mode))
		{
			ft_lstdelnext(previous, NULL);
			return (1);
		}
		previous = previous->next;
	}
	return (0);
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
	stat(file.path, &file.info);
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
