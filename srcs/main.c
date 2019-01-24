/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 18:05:57 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

int		main(int ac, char **av, char **env)
{
	t_prgm			glob;
	char			*pwd;
	int				i;

	i = 0;
	glob.options= 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], "PWD=", 4))
			pwd = ft_strsub(env[i], 4, ft_strlen(&env[i][3]));
		i++;
	}
	glob.pwd = pwd;
	if (ac == 1)
	{
		ft_ls(&glob);
	}
	if (ac > 1)
	{
		if ((i = parsing(ac, av, &glob.options)) == -1)
		{
			ft_printf("usage: ft_ls [-%s] [file ...]\n", OPTIONS);
			return (1);
		}
		if (i == ac)
			ft_ls(&glob);
		else
		{
			while (i < ac)
			{
				if (ft_strequ(av[i], "~"))
				{
					//segfault ???
					glob.pwd = ft_strdup("/Users");
					ft_printf("%s\n", glob.pwd);
				}
				else
					glob.pwd = ft_strdup(pwd);
				ft_asprintf(&glob.pwd, "/%s",  av[i]);
				ft_printf("i = %d ; glob.pwd = %s \n", i, glob.pwd);
				ft_ls(&glob);
				free(glob.pwd);
				i++;
			}
		}
		ft_printf("%.8b\n", glob.options);	
	}
	return (0);
}
