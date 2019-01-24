/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 13:34:54 by cempassi         ###   ########.fr       */
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
			create_list(current, tmp->path, &tmp->dirlist, glob);
			ft_putchar('\n');
			print_list(tmp->dirlist);
			backtrack(tmp->dirlist, glob);
			ft_lstdel(&(tmp->dirlist), del_node);
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

	current = opendir(glob->pwd);
	files_list = NULL;
	create_list(current, glob->pwd, &files_list, glob);
	print_list(files_list);
	if(glob->option & LS_RR)
		backtrack(files_list, glob);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}
