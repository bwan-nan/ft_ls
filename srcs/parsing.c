/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:00:07 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/23 17:51:34 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_strchr_index(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int		flags_handling(char *str, unsigned char *flags)
{
	int		n;

	while(*(++str))
	{
		if ((n = ft_strchr_index(OPTIONS, *str)) == -1)
			return (-1);
		*flags |= (1 << n);
		if ((*str == 'l') || (*str == '1'))
			*flags &= (*str == 'l') ? ~LS_1 : ~LS_L;
	}
	return (1);
}

int				parsing(int ac, char **av, unsigned char *flags)
{
	int	i;

	i = 0;
	if (ac > 1)
	{
		if (av[1][0] == '-' && av[1][1])
		{
			while (++i < ac)
			{
				if (av[i][1] == '-' && av[i][2] == '-' && !av[i][2])
					return (i + 1);
				if (flags_handling(av[i], flags) == -1)
					return (-1);
			}
		}
	}
	return (i);
}
