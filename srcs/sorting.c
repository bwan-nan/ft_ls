/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:21:04 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/04 21:13:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_last_access(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (file1->info.st_atime < file2->info.st_atime);
}

int		sort_ascii(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (ft_strcmp(file1->name, file2->name));
}

int		sort_size(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (file1->info.st_size < file2->info.st_size);
}

int		sort_time_modified(void *a, void *b)
{
	t_status	*file1;
	t_status	*file2;

	file1 = (t_status *)a;
	file2 = (t_status *)b;
	return (file1->info.st_mtime < file2->info.st_mtime);
}

void	sort_list(t_list **files_list, t_prgm *glob)
{
	if (!(glob->option & LS_F))
	{
		if (glob->option & LS_S)
			ft_mergesort(files_list, sort_size);
		else if (glob->option & LS_T)
			ft_mergesort(files_list, &sort_time_modified);
		else
			ft_mergesort(files_list, &sort_ascii);
		if (glob->option & LS_R)
			ft_lstrev(files_list);
	}
}
