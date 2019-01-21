/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/21 18:57:59 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_len(int number)
{
	int		i;

	i = 1;
	while (number /= 10)
		i++;
	return (i);
}

void			get_the_right_size(t_list *files_list, int *tab)
{
	t_status	*tmp;
	int			len;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		if ((len = get_len(tmp->info.st_nlink)) > tab[0])
			tab[0] = len;
		if ((len = get_len(tmp->info.st_size)) > tab[1])
			tab[1] = len;
		tab[2] += tmp->info.st_blocks;
		files_list = files_list->next;
	}
}
