/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:27:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/05 17:29:07 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>
#include <sys/xattr.h>

void	print_xattr(t_status *file, char *xattr)
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
