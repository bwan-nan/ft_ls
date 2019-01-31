/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/31 23:48:29 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

void	list_directory_args(t_prgm *glob, t_list *dir_lst, int flag)
{
	DIR			*current;
	t_status	*tmp;

	while (dir_lst)
	{
		tmp = (t_status *)(dir_lst->data);
		if ((current = opendir(tmp->path)))
			listonedir(glob, current, tmp, flag);
		else
			error(tmp);
		dir_lst = dir_lst->next;
		flag++;
	}
}

void	valid_arg(t_status *tmp, t_list **file, t_list **dir)
{
	if (!S_ISDIR(tmp->info.st_mode))
		ft_lstaddback(file, ft_lstnew(tmp, sizeof(t_status)));
	else if (S_ISDIR(tmp->info.st_mode))
		ft_lstaddback(dir, ft_lstnew(tmp, sizeof(t_status)));
}

void	generate_lists(t_prgm *glob, t_list **file, t_list **dir)
{
	t_list		*args;
	t_status	tmp;

	args = glob->args;
	while (args && !(tmp.path = NULL))
	{
		tmp.dirlist = NULL;
		tmp.name = ft_strdup((char *)args->data);
		if (*(char *)args->data != '/' && *(char *)args->data != '.')
			ft_asprintf(&tmp.path, "./%s", tmp.name);
		else
			ft_asprintf(&tmp.path, "%s", (char *)args->data);
		lstat(tmp.path, &tmp.info) == 0 ? valid_arg(&tmp, file, dir) : error(&tmp);
		args = args->next;
	}
}

int		list_files(t_prgm *glob)
{
	t_list		*file;
	t_list		*dir;
	int			flag;

	file = NULL;
	dir = NULL;
	flag = -1;
	generate_lists(glob, &file, &dir);
	sort_list(&dir, glob);
	sort_list(&file, glob);
	output_handler(file, glob);
	flag += file ? 1 : 0;
	if (dir)
		flag += dir->next ? 1 : 0;
	list_directory_args(glob, dir, flag);
	return (0);
}
