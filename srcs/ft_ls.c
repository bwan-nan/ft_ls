/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 06:22:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_node(t_list *node)
{
	ft_printf("args  = %s\n", ((t_status *)(node->data))->name);
}

int		listalldir(t_list *files_list, t_prgm *glob)
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
				output_handler(tmp->dirlist, glob);
				ft_putchar('\n');
				if(glob->option & LS_RR)	
					listalldir(tmp->dirlist, glob);
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
		listalldir(files_list, glob);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}

t_list		*search_dir(t_prgm *glob, char *path, char *name)
{
	DIR			*current;
	t_list		*tmp;
	t_list		*node;

	tmp = NULL;
	node = NULL;
	if ((current = opendir(path)))
	{
		create_list(current, path, &tmp, glob);
		if ((node = ft_lstfilter(&tmp, name, file_name_filter)))
		{
			ft_strdel(&((t_status *)node->data)->name);
			((t_status *)node->data)->name = ft_strdup(glob->dir);
		}
		ft_lstdel(&tmp, del_node);
		closedir(current);
	}
	return (node);
}

t_list	*access_file(t_prgm *glob, t_list *main_list, char *path)
{
	char		*slash;
	char		*hold;
	t_list		*sub_lst;
	t_list		*args;

	sub_lst = NULL;
	if (!glob->args)
		return (main_list);
	args = glob->args;
	while (args)
	{
		if((slash = ft_strrchr((char *)args->data, '/')))
		{
			hold = (char *)args->data;
			ft_strcpy(glob->dir, hold);
			*hold == '/' ? ft_asprintf(&path, "%.*s", slash - hold, hold)
				: ft_asprintf(&path, "./%.*s", slash - hold, hold);
			ft_lstaddback(&sub_lst, search_dir(glob, path, slash + 1));
			ft_strdel(&path);
		}
		args = args->next;
	}
	return (ft_lstmerge(&main_list, sub_lst));
}

t_list	*dir_node(t_prgm *glob, char *path, char *name, t_status *file)
{
	DIR		*current;
	t_list	*node;
	t_list	*destroy;

	node = NULL;
	if ((current = opendir(path)))
	{
		destroy = ft_lstfilter(&glob->args, name, dir_name_filter);
		ft_lstdel(&destroy, NULL);
		file->name = NULL;
		file->dirlist = NULL;
		stat(file->path, &file->info);
		ft_asprintf(&file->name, "%s", name);
		node = ft_lstnew(file, sizeof(t_status));
		return (node);
	}
	return (node);
}

void	access_dir(t_prgm *glob, t_list **dir)
{
	t_status	file;
	t_list 		*args;

	file.path = NULL;
	if (!glob->args)
		return ;
	args = glob->args;
	if (*((char *)((args)->data)) == '/' )
		ft_asprintf(&file.path, "%s", (char *)(args)->data);
	else
		ft_asprintf(&file.path, "./%s", (char *)(args)->data);
	while (args)
	{
		ft_lstaddback(dir, dir_node(glob, file.path, args->data, &file));	
		args = args->next;
	}
	return ;
}


int		list_files(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*main_lst;
	t_list		*file_lst;
	t_list		*dir_lst;

	main_lst = NULL;
	current = opendir(path);
	ft_strcpy(glob->dir, path);
	create_list(current, path, &main_lst, glob);
	file_lst = ft_lstfilter(&main_lst, glob, file_filter);
	file_lst = access_file(glob, file_lst, NULL);
	dir_lst = ft_lstfilter(&main_lst, glob, dir_filter);
	access_dir(glob, &dir_lst);
	output_handler(file_lst, glob);
	listalldir(dir_lst, glob);
	ft_lstdel(&file_lst, NULL);
	ft_lstdel(&dir_lst, NULL);
	ft_lstdel(&main_lst, del_node);
	closedir(current);
	return (0);
}
