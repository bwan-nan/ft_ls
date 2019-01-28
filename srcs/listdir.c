/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 07:04:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/28 11:19:39 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		listalldir(t_prgm *glob, t_list *files_list)
{
	DIR			*current;
	t_status	*tmp;

	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		if (S_ISDIR(tmp->info.st_mode) && !ft_strequ(tmp->name, ".")
				&& !ft_strequ(tmp->name, ".."))
		{
			current = opendir(tmp->path);
			ft_strcpy(glob->dir, tmp->path);
			create_list(current, tmp->path, &tmp->dirlist, glob);
			if (tmp->dirlist)
			{
				ft_putchar('\n');
				output_handler(tmp->dirlist, glob);
				if(glob->option & LS_RR)	
					listalldir(glob, tmp->dirlist);
				ft_lstdel(&(tmp->dirlist), del_node);
			}
			closedir(current);
		}
		files_list = files_list->next;
	}
	return (0);
}

int		list_directory(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*files_list;

	current = opendir(path);
	files_list = NULL;
	ft_strcpy(glob->dir, path);
	create_list(current, path, &files_list, glob);
	output_handler(files_list, glob);
	if(glob->option & LS_RR)
		listalldir(glob, files_list);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}

