/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/13 19:45:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>

static void		glob_init(t_prgm *glob)
{
	int			i;

	i = 0;
	glob->args = NULL;
	glob->args_count = 0;
	glob->ls_colors = NULL;
	glob->error = 0;
	ft_bzero(glob->dir, DIR_MAX);
	ioctl(0, TIOCGWINSZ, &glob->window);
	while (i <= 10)
		glob->colors[i++] = NULL;
}

static void		glob_del(t_prgm *glob)
{
	int			i;

	i = 0;
	ft_strdel(&glob->ls_colors);
	ft_lstdel(&glob->args, NULL);
	if (glob->option & LS_G)
	{
		while (i <= 10)
			ft_strdel(&glob->colors[i++]);
	}
}

static int		illegal_option(t_prgm *glob)
{
	char	*illegal;
	char	*usage;

	illegal = "ft_ls: illegal option -- ";
	usage = "usage: ft_ls [-";
	ft_dprintf(2, "%s%c\n%s%s] [file ...]\n"
			, illegal, glob->optopt, usage, OPTION);
	return (1);
}

int				main(int ac, char **av, char **env)
{
	t_prgm			glob;

	glob_init(&glob);
	if ((glob.option = options(ac, av, &glob)) == '?')
		return (illegal_option(&glob));
	get_env(env, &glob);
	if (!isatty(1))
	{
		if (glob.option & LS_G)
			glob.option &= ~LS_G;
		if (!(glob.option & (LS_L + LS_M + LS_C + LS_X)))
			option_cancel(&glob.option, '1');
	}
	if (glob.option & LS_G)
		init_colors(&glob);
	if (!glob.error)
	{
		if (ac > 1)
			glob.args = ft_getargslst(ac, av);
		glob.args == NULL ? list_directory(&glob, ".") : list_files(&glob);
	}
	glob_del(&glob);
	return (glob.error);
}
