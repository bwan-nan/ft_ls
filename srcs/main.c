/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/01 12:11:15 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		glob_init(t_prgm *glob)
{
	glob->pwd = NULL;
	glob->home = NULL;
	glob->args = NULL;
	glob->args_count = 0;
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

	glob_init(&glob);
	get_env(env, &glob);
	if ((glob.option = options(ac, av, &glob)) == '?')
		return (illegal_option(&glob));
	glob.args = ft_getargslst(ac, av);
	glob.args == NULL ? list_directory(&glob, ".") : list_files(&glob);
	glob_del(&glob);
	return (0);
}
