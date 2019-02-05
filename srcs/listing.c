/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 07:04:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/05 21:55:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			listonedir(t_prgm *glob, DIR *current, t_status *tmp)
{
	if (create_list(current, tmp->path, &tmp->dirlist, glob) == 2)
	{
		ft_lstdel(&tmp->dirlist, del_node);
		return (glob->error);
	}
	sort_list(&tmp->dirlist, glob);
	if (tmp->dirlist)
	{
		if (glob->args_count == 2)
			ft_putchar('\n');
		output_handler(glob, tmp->dirlist);
		if (glob->option & LS_RR)
			listalldir(glob, tmp->dirlist, NULL);
		ft_lstdel(&(tmp->dirlist), del_node);
	}
	closedir(current);
	return (0);
}

int			listalldir(t_prgm *glob, t_list *lst, t_status *tmp)
{
	DIR			*current;
	int			flag;

	while (lst && (tmp = (t_status *)(lst->data)))
	{
		flag = S_ISDIR(tmp->info.st_mode);
		if (flag && !ft_strequ(tmp->name, ".") && !ft_strequ(tmp->name, ".."))
		{
			ft_strcpy(glob->dir, tmp->path);
			if ((current = opendir(tmp->path)))
			{
				if (listonedir(glob, current, tmp) == 2)
					return (glob->error);
			}
			else
			{
				ft_putchar('\n');
				error(glob, tmp);
			}
		}
		lst = lst->next;
	}
	return (0);
}

static int	list_directory_args(t_prgm *glob, t_list *dir_lst)
{
	DIR			*current;
	t_status	*tmp;

	while (dir_lst)
	{
		tmp = (t_status *)(dir_lst->data);
		ft_strcpy(glob->dir, tmp->path);
		if ((current = opendir(tmp->path)))
		{
			if (listonedir(glob, current, tmp) == 2)
				return (glob->error);
		}
		else
			error(glob, tmp);
		ft_lstpop(&dir_lst, del_node);
	}
	return (0);
}

int			list_directory(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*files;

	current = opendir(path);
	files = NULL;
	ft_strcpy(glob->dir, path);
	if (create_list(current, path, &files, glob) != 2)
	{
		sort_list(&files, glob);
		output_handler(glob, files);
		if (glob->option & LS_RR)
			listalldir(glob, files, NULL);
	}
	ft_lstdel(&files, del_node);
	closedir(current);
	return (0);
}

int			list_files(t_prgm *glob)
{
	t_list		*file;
	t_list		*dir;

	file = NULL;
	dir = NULL;
	if (generate_lists(glob, glob->args, &file, &dir) != 2)
	{
		if (file)
			sort_list(&file, glob);
		sort_list(&dir, glob);
		output_handler(glob, file);
		if (glob->args->next && file && dir)
			glob->args_count = 2;
		else if (glob->args->next)
			glob->args_count = 1;
		list_directory_args(glob, dir);
	}
	ft_lstdel(&file, del_node);
	return (0);
}
