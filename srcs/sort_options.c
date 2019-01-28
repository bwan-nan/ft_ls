/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:19:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/28 16:31:22 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** sort by default (in ascii order)
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
** option -S (sort files by size)
*/

int		sort_by_size(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (file1->info.st_size < file2->info.st_size);
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
	return (file1->info.st_mtime < file2->info.st_mtime);
}

/*
** option -u (sort by time of last access)
** NOT WORKING: statx to be added ?
*/ 

int		sort_last_access(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (file1->info.st_atime < file2->info.st_atime);
}
