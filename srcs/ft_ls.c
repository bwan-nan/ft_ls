/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/23 23:05:10 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*create_list(DIR *current, char *path)
{
	t_status	file;
	t_list		*files_list;
	t_list		*node;

	files_list = NULL;
	file.path = NULL;
	while ((file.dirent = readdir(current)))
	{
		ft_asprintf(&file.path, "%s/%s", path, file.dirent->d_name);
		stat(file.path, &file.info);
		node = ft_lstnew(&file, sizeof(t_status));
		((t_status *)(node->data))->path = ft_strdup(file.path);
		ft_lstaddback(&files_list, node);
		ft_strdel(&file.path);
	}
	return (files_list);
}

int		backtrack(t_list *files_list)
{
	t_status	*tmp;
	char		*holder;
	DIR			*current;

	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		if (S_ISDIR(tmp->info.st_mode) && !ft_strequ(tmp->dirent->d_name, ".")
				&& !ft_strequ(tmp->dirent->d_name, ".."))
		{
			holder = tmp->path;
			tmp->dirlist = create_list((current = opendir(tmp->path)), tmp->path);
			ft_putchar('\n');
			print_list(tmp->dirlist);
			backtrack(tmp->dirlist);
			closedir(current);
			ft_lstdel(&(tmp->dirlist), NULL);
			ft_strdel(&holder);
		}
		files_list = files_list->next;
	}
	return (0);
}

int		ft_ls(t_prgm *glob)
{
	DIR			*current;
	t_list		*files_list;

	current = opendir(glob->pwd);
	files_list = create_list(current, glob->pwd);
	print_list(files_list);
	if(glob->option & LS_RR)
		backtrack(files_list);
	closedir(current);
	return (0);
}
