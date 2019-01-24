/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 20:22:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		backtrack(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	DIR			*current;

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
				print_list(tmp->dirlist, glob);
				backtrack(tmp->dirlist, glob);
				ft_lstdel(&(tmp->dirlist), del_node);
			}
			closedir(current);
		}
		files_list = files_list->next;
	}
	return (0);
}

int		ft_ls(t_prgm *glob)
{
	DIR			*current;
	t_list		*files_list;

	current = opendir(".");
	files_list = NULL;
	ft_strcpy(glob->dir, ".");
	create_list(current, ".", &files_list, glob);
	print_list(files_list, glob);
	if(glob->option & LS_RR)
		backtrack(files_list, glob);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}
