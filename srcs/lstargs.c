/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 13:15:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*search_file(t_prgm *glob, char *path, char *name)
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
			ft_lstaddback(&sub_lst, search_file(glob, path, slash + 1));
			ft_strdel(&path);
		}
		args = args->next;
	}
	return (ft_lstmerge(&main_list, sub_lst));
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

void	list_directory_args(t_prgm *glob, t_list *dir_lst)
{
	DIR			*current;
	t_status	*tmp;
	char		turn;

	turn = 0;
	while (dir_lst)
	{
		tmp = (t_status *)(dir_lst->data);
		current = opendir(tmp->path);
		if (turn == 0 && !dir_lst->next)
			ft_strcpy(glob->dir, ".");
		else 
			ft_strcpy(glob->dir, tmp->path);
		create_list(current, tmp->path, &tmp->dirlist, glob);
		output_handler(tmp->dirlist, glob);
		if (glob->option & LS_RR)
			listalldir(glob, tmp->dirlist);
		ft_lstdel(&(tmp->dirlist), del_node);
		closedir(current);
		dir_lst = dir_lst->next;
		if (dir_lst)
			ft_putchar('\n');
		turn++;
	}
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
	//ft_lstiter(glob->args, error_output);
	output_handler(file_lst, glob);
	if (dir_lst && file_lst)
		ft_putchar('\n');
	list_directory_args(glob, dir_lst);
	ft_lstdel(&file_lst, NULL);
	ft_lstdel(&dir_lst, NULL);
	ft_lstdel(&main_lst, del_node);
	closedir(current);
	return (0);
}
