/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/25 17:42:35 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned int	basic(char c, unsigned char option)
{
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
	if (c == 't')
		option |= LS_T;
	if (c == 'u')
		option |= LS_U;
	if (c == 'f')
	{
		option |= LS_U;
		option |= LS_A;
	}
	return (option);
}

unsigned int	options(int ac, char **av)
{
	int				c;
	unsigned int	option;

	option = 0;
	while ((c = ft_getopt(ac, av, OPTION)) != -1)
	{
		if (c == 0)
			return (0);
		if (c == '?')
			return ('?');
		option = basic(c, option);
	}
	return (option);
}

static void		glob_init(t_prgm *glob)
{
	glob->pwd = NULL;
	glob->home = NULL;
	glob->args = NULL;
	ft_bzero(glob->dir, DIR_MAX);
}

static void		glob_del(t_prgm *glob)
{
	ft_strdel(&glob->pwd);
	ft_strdel(&glob->home);
	ft_memdel((void **)(&glob->args));
}

unsigned int	get_env(char **env, t_prgm *glob)
{
	int		i;

	i = 0;

	while (env[i])
	{
		if (ft_strnequ(env[i], "PWD=", 4))
			glob->pwd = ft_strsub(env[i], 4, ft_strlen(&env[i][3]));
		if (ft_strnequ(env[i], "HOME=", 5))
			glob->home = ft_strsub(env[i], 5, ft_strlen(&env[i][3]));
		i++;
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	t_prgm			glob;
	int				i;

	i= 0;
	glob_init(&glob);
	glob.option = 0;
	get_env(env, &glob);
	if ((glob.option = options(ac, av)) == '?')
		return (ft_printf("usage: ft_ls [-%s] [file ...]\n", OPTION) ? 1 : 0);
	glob.args = ft_getargs(ac, av);
	if (glob.args == NULL)
		list_directory(&glob, ".");
	else
		list_files(&glob, ".");
	ft_printf("%.8b\n", glob.option);
	glob_del(&glob);
	return (0);
}
