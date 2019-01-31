/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getargscount.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:29:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/31 21:38:39 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_getargscount(int ac, char **av)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (i < ac && av[i][0] == '-')
		i++;
	while (i + count < ac)
		count++;
	return (count);
}
