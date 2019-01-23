/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/23 18:03:59 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	unsigned char	flags;
	int				i;

	if (ac == 1)
		ft_ls(flags);
	if (ac > 1)
	{
		if ((i = parsing(ac, av, &flags)) == -1)
			return (1);
		if (flags & LS_R)
			ft_ls(flags);
	}
	return (0);
}
