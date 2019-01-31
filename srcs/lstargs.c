/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/30 16:32:03 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_path(char **args, char **name, int i)
{
	DIR		*current;
	char	*path;
	char	*holder;

	if (!args)
		return (0);
	path = NULL;
	ft_asprintf(&path, "/%s", args[0]);
	while (*(args + 1 + i++))
	{
		if ((current = opendir(path)))
		{
			holder = NULL;
			ft_asprintf(&holder, "%s/%s", path, args[i]);
			ft_strdel(&path);
			path = holder;
			closedir(current);
		}
		else
		{
			return (0);
		}
	}
	*name = ft_strdup(args[i - 1]);
	ft_freetab(&args);
	return (1);
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
			listalldir(glob, tmp->dirlist, NULL);
		ft_lstdel(&(tmp->dirlist), del_node);
		closedir(current);
		if ((dir_lst = dir_lst->next))
			ft_putchar('\n');
		turn++;
	}
}

void	current_dir(t_status *tmp, t_list **file, t_list **dir)
{
	if (!S_ISDIR(tmp->info.st_mode))
		ft_lstaddback(file, ft_lstnew(tmp, sizeof(t_status)));
	else if (S_ISDIR(tmp->info.st_mode))
		ft_lstaddback(dir, ft_lstnew(tmp, sizeof(t_status)));
}

void	generate_list(t_prgm *glob, t_list **file, t_list **dir, t_list **error)
{
	t_list		*args;
	t_status	tmp;

	args = glob->args;
	while (args && !(tmp.path = NULL))
	{
		tmp.dirlist = NULL;
		if (*(char *)args->data != '/')
		{
			tmp.name = ft_strdup((char *)args->data);
			ft_asprintf(&tmp.path, "./%s", tmp.name);
		}
		else if (check_path(ft_strsplit((char *)args->data, "/"), &tmp.name, 0))
			ft_asprintf(&tmp.path, "%s", (char *)args->data);
		if (lstat(tmp.path, &tmp.info) == 0)
			current_dir(&tmp, file, dir);
		else
			ft_lstaddback(error, ft_lstnew(&tmp, sizeof(t_status)));
		args = args->next;
	}
}

int		list_files(t_prgm *glob)
{
	t_list		*file;
	t_list		*dir;
	t_list		*error;

	file = NULL;
	dir = NULL;
	error = NULL;
	if (glob)
		sort_list(&glob->args, glob);
	generate_list(glob, &file, &dir, &error);
	output_handler(file, glob);
	list_directory_args(glob, dir);
	return (0);
}
