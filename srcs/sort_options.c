/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:19:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/25 18:00:49 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** option -l (in ascii order)
*/

int		sort_ascii(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (ft_strcmp(file1->name, file2->name));
}

/*
** option -t (sort by time modified: most recently modified first)
*/

int		sort_time_modified(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	if (file1->info.st_mtime < file2->info.st_mtime)
		return (1);
	return (0);
}

/*
** option -u (sort by time of last access
*/

int		sort_last_access(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	if (file1->info.st_atime < file2->info.st_atime)
		return (1);
	return (0);
}
