/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:27:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/05 01:27:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>
#include <sys/xattr.h>

void	print_xattr(t_status *file, char *xattr)
{
	int		len;
	ssize_t	size;

	if (!file->xattr_len)
		return ;
	len = 0;
	size = getxattr(file->path, &xattr[len], NULL, 0, 0, XATTR_NOFOLLOW);
	ft_putchar('\n');
	ft_printf("          %s       %d", xattr, size);	
	len = ft_strlen(&xattr[len]);
	file->xattr_len -= len + 1;
	len++;
	return (print_xattr(file, &xattr[len]));
}
