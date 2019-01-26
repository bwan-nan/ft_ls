/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 14:00:27 by cempassi         ###   ########.fr       */
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

void		glob_del(t_prgm *glob)
{
	ft_strdel(&glob->pwd);
	ft_strdel(&glob->home);
	ft_strdel(&glob->colors);
	ft_lstdel(&glob->args, NULL);
}

int				main(int ac, char **av, char **env)
{
	t_prgm			glob;
	int				i;

	i= 0;
	glob_init(&glob);
	get_env(env, &glob);
	ft_printf("%s \n%s\n%s\n", glob.pwd, glob.home, glob.colors);
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
