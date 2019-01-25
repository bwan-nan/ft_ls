/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/01/24 16:51:25 by bwan-nan         ###   ########.fr       */
=======
/*   Updated: 2019/01/25 14:43:45 by cempassi         ###   ########.fr       */
>>>>>>> sandbox
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
<<<<<<< HEAD
			create_list((current = opendir(tmp->path)), tmp->path, &tmp->dirlist, glob);
			ft_putchar('\n');
			print_list(tmp->dirlist);
			backtrack(tmp->dirlist, glob);
			ft_lstdel(&(tmp->dirlist), del_node);
=======
			current = opendir(tmp->path);
			ft_strcpy(glob->dir, tmp->path);
			create_list(current, tmp->path, &tmp->dirlist, glob);
			if (tmp->dirlist)
			{
				ft_putchar('\n');
				output_handler(tmp->dirlist, glob);
				backtrack(tmp->dirlist, glob);
				ft_lstdel(&(tmp->dirlist), del_node);
			}
>>>>>>> sandbox
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
<<<<<<< HEAD
	create_list(current, glob->pwd, &files_list, glob);
	if (glob->options & LS_L)
		merge_sort(&files_list, &sort_ascii);
	print_list(files_list);
	if(glob->options & LS_R)
=======
	ft_strcpy(glob->dir, path);
	create_list(current, path, &files_list, glob);
	output_handler(files_list, glob);
	if(glob->option & LS_RR)
>>>>>>> sandbox
		backtrack(files_list, glob);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}

int		list_files(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*files_list;
	t_list		*sub_file_list;
	t_list		*sub_dir_list;
	
	current = opendir(path);
	sub_file_list = NULL;
	files_list = NULL;
	ft_strcpy(glob->dir, path);
	create_list(current, path, &files_list, glob);
	sub_file_list = ft_lstfilter(files_list, glob, name_filter);
	output_handler(sub_file_list, glob);
	return (0);
}
