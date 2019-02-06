/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/06 16:30:37 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <grp.h>
#include <pwd.h>

static void	init_status(t_status *info)
{
	info->acl = NULL;
	info->xattr = NULL;
	info->path = NULL;
	info->name = NULL;
	info->chmod = NULL;
	info->grp = NULL;
	info->pwd = NULL;
	info->dirlist = NULL;
	info->acl_tab = NULL;
}

static int	get_chmod(t_prgm *glob)
{
	char	*buf[DIR_MAX];
	char	*acl;

	if (!(glob->tmp.chmod = str_chmod(&glob->tmp, (char *)buf)))
		return (glob->error = 2);
	if (glob->tmp.chmod[10] == '@' && glob->option & LS_AR)
	{
		if (!(glob->tmp.xattr = ft_strnew(glob->tmp.xattr_len)))
			return (glob->error = 2);
		glob->tmp.xattr = ft_memcpy(glob->tmp.xattr, buf, glob->tmp.xattr_len);
	}
	if (glob->tmp.acl && glob->option & LS_E)
	{
		if (!(acl = acl_to_text(glob->tmp.acl, 0)))
			return (glob->error = 2);
		if (!(glob->tmp.acl_tab = ft_strsplit(acl, ":\n")))
			return (glob->error = 2);
	}
	if ((glob->holder = getgrgid(glob->tmp.info.st_gid)))
		if (!(glob->tmp.grp = ft_strdup(((t_group *)glob->holder)->gr_name)))
			return (glob->error = 2);
	if ((glob->holder = getpwuid(glob->tmp.info.st_uid)))
		if (!(glob->tmp.pwd = ft_strdup(((t_passwd *)glob->holder)->pw_name)))
			return (glob->error = 2);
	return (0);
}

int			generate_lists(t_prgm *glob, t_list *args, t_list **file\
			, t_list **dir)
{
	t_list	*node;

	if (!args)
		return (0);
	init_status(&glob->tmp);
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
		if (S_ISDIR(glob->tmp.info.st_mode))
			ft_lstaddback(dir, node);
		else
			ft_lstaddback(file, node);
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
		return (1);
	if (!(glob->option & LS_A) && !(glob->option & LS_F)
			&& ((t_dirent *)glob->holder)->d_name[0] == '.')
		return (create_list(current, path, files_list, glob));
	init_status(&glob->tmp);
	ft_asprintf(&glob->tmp.path, "%s/%s", path
			, ((t_dirent *)glob->holder)->d_name);
	if (!glob->tmp.path)
		return (glob->error = 2);
	lstat(glob->tmp.path, &glob->tmp.info);
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

void		del_node(void **data)
{
	t_status *tmp;

	if (!data || !*data)
		return ;
	tmp = (t_status *)(*data);
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
