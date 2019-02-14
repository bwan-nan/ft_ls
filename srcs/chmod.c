/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chmod.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:15:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/14 11:02:33 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/xattr.h>

static void	extended_chmod(t_status *file, char *p)
{
	mode_t		mode;

	mode = file->info.st_mode;
	p[3] = mode & S_IXUSR ? 'x' : '-';
	p[3] = mode & S_ISUID ? 'S' : p[3];
	p[3] = mode & S_IXUSR && mode & S_ISUID ? 's' : p[3];
	p[6] = mode & S_IXGRP ? 'x' : '-';
	p[6] = mode & S_ISGID ? 'S' : p[6];
	p[6] = mode & S_IXGRP && mode & S_ISGID ? 's' : p[6];
	p[9] = mode & S_IXOTH ? 'x' : '-';
	p[9] = mode & S_ISVTX ? 'T' : p[9];
	p[9] = mode & S_IXOTH && mode & S_ISVTX ? 't' : p[9];
}

static char	*str_chmod(t_status *file, char *buffer)
{
	char	p[12];

	file->xattr_len = listxattr(file->path, buffer, DIR_MAX, XATTR_NOFOLLOW);
	file->acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	p[0] = '\0';
	p[0] = !*p && S_ISSOCK(file->info.st_mode) ? 's' : *p;
	p[0] = !*p && S_ISDIR(file->info.st_mode) ? 'd' : *p;
	p[0] = !*p && S_ISCHR(file->info.st_mode) ? 'c' : *p;
	p[0] = !*p && S_ISBLK(file->info.st_mode) ? 'b' : *p;
	p[0] = !*p && S_ISLNK(file->info.st_mode) ? 'l' : *p;
	p[0] = !*p && S_ISFIFO(file->info.st_mode) ? 'f' : *p;
	p[0] = !*p ? '-' : *p;
	p[1] = file->info.st_mode & S_IRUSR ? 'r' : '-';
	p[2] = file->info.st_mode & S_IWUSR ? 'w' : '-';
	p[4] = file->info.st_mode & S_IRGRP ? 'r' : '-';
	p[5] = file->info.st_mode & S_IWGRP ? 'w' : '-';
	p[7] = file->info.st_mode & S_IROTH ? 'r' : '-';
	p[8] = file->info.st_mode & S_IWOTH ? 'w' : '-';
	extended_chmod(file, p);
	p[10] = file->acl ? '+' : ' ';
	p[10] = file->xattr_len > 0 ? '@' : p[10];
	p[11] = '\0';
	return (ft_strdup(p));
}

int			get_chmod(t_prgm *glob)
{
	char	*buf[DIR_MAX];

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
		if (!(glob->tmp.acl_str = acl_to_text(glob->tmp.acl, 0)))
			return (glob->error = 2);
		if (!(glob->tmp.acl_tab = ft_strsplit(glob->tmp.acl_str, ":\n")))
			return (glob->error = 2);
		ft_strdel(&glob->tmp.acl_str);
	}
	if ((glob->holder = getgrgid(glob->tmp.info.st_gid)))
		if (!(glob->tmp.grp = ft_strdup(((t_group *)glob->holder)->gr_name)))
			return (glob->error = 2);
	if ((glob->holder = getpwuid(glob->tmp.info.st_uid)))
		if (!(glob->tmp.pwd = ft_strdup(((t_passwd *)glob->holder)->pw_name)))
			return (glob->error = 2);
	return (0);
}

void		print_xattr(t_status *file, char *xattr)
{
	int		len;
	ssize_t	size;
	int		xattr_pad;
	int		size_pad;

	if (!file->xattr_len)
		return ;
	xattr_pad = 20;
	size_pad = 10;
	len = 0;
	size = getxattr(file->path, &xattr[len], NULL, 0, 0, XATTR_NOFOLLOW);
	ft_putchar('\n');
	ft_printf("%*s%-*s%*d", 8, "", xattr_pad, xattr, size_pad, size);
	len = ft_strlen(&xattr[len]);
	file->xattr_len -= len + 1;
	len++;
	return (print_xattr(file, &xattr[len]));
}

void		print_acl(t_status *file)
{
	char	**tab;
	size_t	index;

	index = 0;
	tab = file->acl_tab;
	ft_putchar('\n');
	ft_printf(" 0: %s:%s %s %s", tab[1], tab[3], tab[5], tab[6]);
}
