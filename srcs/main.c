/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 07:37:53 by cempassi         ###   ########.fr       */
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
	ft_lstdel(&glob->args, NULL);
}

int				main(int ac, char **av, char **env)
{
	t_prgm			glob;
	int				i;

	i= 0;
	glob_init(&glob);
	glob.option = 0;
	get_env(env, &glob);
	if ((glob.option = options(ac, av)) == '?')
		return (ft_printf("usage: ft_ls [-%s] [file ...]\n", OPTION) ? 1 : 0);
	glob.args = ft_getargslst(ac, av);
	tilde_replace(&glob);
	if (glob.args == NULL)
		list_directory(&glob, ".");
	else
		list_files(&glob, ".");
	glob_del(&glob);
	return (0);
}
