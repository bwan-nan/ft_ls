/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 13:37:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned int	options(int ac, char **av)
{
	int c;
	unsigned int option;

	option = 0;
	while ((c = ft_getopt(ac, av, OPTION)) != -1)	
	{
		if (c == '?')
			return ('?');
		if (c =='l')
		{
			option |= LS_L;
			option &= ~LS_1;
		}
		if (c == '1')
		{
			option |= LS_1;
			option &= ~LS_L;
		}
		if (c == 'R')
			option |= LS_RR;
		if (c == 'a')
			option |= LS_A;
	}
	return (option);
}

int		main(int ac, char **av, char **env)
{
	t_prgm			glob;
	int				i = 0;

	glob.option = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], "PWD=", 4))
			glob.pwd = ft_strsub(env[i], 4, ft_strlen(&env[i][3]));
		i++;
	}
	if (ac == 1)
	{
		ft_ls(&glob);
	}
	if (ac > 1)
	{
		if ((glob.option = options(ac, av)) == '?')
		{
			ft_printf("usage: ft_ls [-%s] [file ...]\n", OPTION);
			return (1);
		}
		ft_ls(&glob);
		ft_printf("%.8b\n", glob.option);	
	}
	return (0);
}
