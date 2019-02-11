/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/11 17:49:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>

static void	make_list(t_list **file, t_list **dir, t_list *node)
{
	t_status	*tmp;
	DIR			*current;

	tmp = (t_status *)node->data;
	if (S_ISDIR(tmp->info.st_mode))
		ft_lstaddback(dir, node);
	else if (S_ISLNK(tmp->info.st_mode))
	{
		if ((current = opendir(tmp->path)))
			ft_lstaddback(dir, node);
		else
			ft_lstaddback(file, node);
		closedir(current);
	}
	else
		ft_lstaddback(file, node);
}

int			generate_lists(t_prgm *glob, t_list *args, t_list **file\
			, t_list **dir)
{
	t_list	*node;

	if (!args)
		return (0);
	ft_bzero(&glob->tmp, sizeof(t_status));
	if (!(glob->tmp.name = ft_strdup((char *)args->data)))
		return (glob->error = 2);
	if (!(glob->tmp.path = ft_strdup(glob->tmp.name)))
		return (glob->error = 2);
	if (lstat((char *)args->data, &glob->tmp.info) == 0)
	{
		if (glob->option & LS_L || glob->option & LS_AR)
			if (get_chmod(glob) == 2)
				return (2);
		if (!(node = ft_lstnew(&glob->tmp, sizeof(t_status))))
			return (glob->error = 2);
		make_list(file, dir, node);
	}
	else
		error(glob, &glob->tmp);
	return (generate_lists(glob, args->next, file, dir));
}

int			create_list(DIR *current, char *path, t_list **files_list\
			, t_prgm *glob)
{
	t_list		*node;

	if (!(glob->holder = (void *)readdir(current)))
		return (0);
	if (!(glob->option & LS_A) && !(glob->option & LS_F)
			&& ((t_dirent *)glob->holder)->d_name[0] == '.')
		return (create_list(current, path, files_list, glob));
	ft_bzero(&glob->tmp, sizeof(t_status));
	ft_asprintf(&glob->tmp.path, "%s/%s", path
			, ((t_dirent *)glob->holder)->d_name);
	if (!glob->tmp.path)
		return (glob->error = 2);
	if (lstat(glob->tmp.path, &glob->tmp.info) != 0)
		return (glob->error = 2);
	if (!(glob->tmp.name = ft_strdup(((t_dirent *)glob->holder)->d_name)))
		return ((glob->error = 2));
	if (glob->option & LS_L || glob->option & LS_AR)
		get_chmod(glob);
	if (!(node = ft_lstnew(&glob->tmp, sizeof(t_status))))
		if (get_chmod(glob) == 2)
			return (2);
	ft_lstaddback(files_list, node);
	return (create_list(current, path, files_list, glob));
}

void		del_node(void *data)
{
	t_status *tmp;

	if (!data)
		return ;
	tmp = (t_status *)(data);
	if (tmp->acl_tab)
		ft_freetab(&tmp->acl_tab);
	if (tmp->acl)
		acl_free(tmp->acl);
	if (tmp->xattr)
		ft_strdel(&tmp->xattr);
	if (tmp->path)
		ft_strdel(&tmp->path);
	if (tmp->name)
		ft_strdel(&tmp->name);
	if (tmp->chmod)
		ft_strdel(&tmp->chmod);
	if (tmp->grp)
		ft_strdel(&tmp->grp);
	if (tmp->pwd)
		ft_strdel(&tmp->pwd);
}
