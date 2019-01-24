/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:19:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/24 17:08:07 by bwan-nan         ###   ########.fr       */
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
