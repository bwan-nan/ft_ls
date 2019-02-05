/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/05 17:28:33 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_status(t_status *info)
{
	info->path = NULL;
	info->name = NULL;
	info->chmod = NULL;
	info->grp = NULL;
	info->pwd = NULL;
	info->dirlist = NULL;
}

void	permissions(t_prgm *glob)
{
	char	*buf[DIR_MAX];

	glob->tmp.chmod = getchmod(&glob->tmp, (char *)buf);
	if (glob->tmp.chmod[10] == '@')
	{
		glob->tmp.xattr = ft_strnew(glob->tmp.xattr_len);
		glob->tmp.xattr = ft_memcpy(glob->tmp.xattr, buf, glob->tmp.xattr_len);
	}
	if ((glob->holder = getgrgid(glob->tmp.info.st_gid)))
		glob->tmp.grp = ft_strdup(((t_group *)glob->holder)->gr_name);
	if ((glob->holder = getpwuid(glob->tmp.info.st_uid)))
		glob->tmp.pwd = ft_strdup(((t_passwd *)glob->holder)->pw_name);
}

void	generate_lists(t_prgm *glob, t_list *args, t_list **file, t_list **dir)
{
	if (!args)
		return ;
	init_status(&glob->tmp);
	glob->tmp.name = ft_strdup((char *)args->data);
	glob->tmp.path = ft_strdup(glob->tmp.name);
	if (lstat((char *)args->data, &glob->tmp.info) == 0)
	{
		if (glob->option & LS_L || glob->option & LS_AR)
			permissions(glob);
		if (S_ISDIR(glob->tmp.info.st_mode))
			ft_lstaddback(dir, ft_lstnew(&glob->tmp, sizeof(t_status)));
		else
			ft_lstaddback(file, ft_lstnew(&glob->tmp, sizeof(t_status)));
	}
	else
		error(glob, &glob->tmp);
	return (generate_lists(glob, args->next, file, dir));
}

int		create_list(DIR *current, char *path, t_list **files_list, t_prgm *glob)
{
	if (!(glob->holder = (void *)readdir(current)))
		return (1);
	if (!(glob->option & LS_A) && !(glob->option & LS_F)
			&& ((t_dirent *)glob->holder)->d_name[0] == '.')
		return (create_list(current, path, files_list, glob));
	init_status(&glob->tmp);
	ft_asprintf(&glob->tmp.path, "%s/%s", path
			, ((t_dirent *)glob->holder)->d_name);
	lstat(glob->tmp.path, &glob->tmp.info);
	glob->tmp.name = ft_strdup(((t_dirent *)glob->holder)->d_name);
	if (glob->option & LS_L || glob->option & LS_AR)
		permissions(glob);
	ft_lstaddback(files_list, ft_lstnew(&glob->tmp, sizeof(t_status)));
	return (create_list(current, path, files_list, glob));
}

void	del_node(void **data)
{
	t_status *tmp;

	if (!data || !*data)
		return ;
	tmp = (t_status *)(*data);
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
