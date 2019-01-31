/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/31 13:16:48 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	ft_strdel(&glob->colors);
	ft_lstdel(&glob->args, NULL);
}

static int		illegal_option(t_prgm *glob)
{
	char	*illegal;
	char	*usage;

	illegal = "ft_ls: illegal option -- ";
	usage = "usage: ft_ls [-";
	ft_dprintf(2, "%s%c\n%s%s] [file ...]\n"
				, illegal, glob->optopt, usage,  OPTION);
	return (1);
}

int				main(int ac, char **av, char **env)
{
	t_prgm			glob;
	int				i;

	i = 0;
	glob_init(&glob);
	get_env(env, &glob);
	if ((glob.option = options(ac, av, &glob)) == '?')
		return (illegal_option(&glob));
	glob.args = ft_getargslst(ac, av);
	if (glob.args == NULL)
		list_directory(&glob, ".");
	else
		list_files(&glob);
	glob_del(&glob);
	return (0);
}
