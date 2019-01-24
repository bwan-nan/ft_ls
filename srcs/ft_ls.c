/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 12:52:01 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*create_list(DIR *current, char *path)
{
	t_status	file;
	t_list		*files_list;
	char		*holder;

	files_list = NULL;
	while ((file.dirent = readdir(current)))
	{
		file.path = ft_strjoin(path, "/");
		holder = ft_strjoin(file.path, file.dirent->d_name);
		stat(holder, &file.info);
		ft_strdel(&file.path);
		file.path = holder;
		ft_lstaddback(&files_list, ft_lstnew(&file, sizeof(t_status)));
	}
	return (files_list);
}

int		backtrack(t_list *files_list)
{
	t_status	*tmp;
	char		*holder;

	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		if (S_ISDIR(tmp->info.st_mode) && !ft_strequ(tmp->dirent->d_name, ".")
				&& !ft_strequ(tmp->dirent->d_name, ".."))
		{
			holder = tmp->path;
			tmp->dirlist = create_list(opendir(tmp->path), tmp->path);
			ft_putchar('\n');
			print_list(tmp->dirlist);
			backtrack(tmp->dirlist);
			ft_lstdel(&(tmp->dirlist), del_node);
			ft_strdel(&holder);
		}
		files_list = files_list->next;
	}
	return (0);
}

int		ft_ls(unsigned char flags)
{
	DIR			*current;
	t_list		*files_list;

	current = opendir(".");
	files_list = create_list(current, ".");
	print_list(files_list);
	if (flags & LS_R)
		backtrack(files_list);
	return (0);
}
