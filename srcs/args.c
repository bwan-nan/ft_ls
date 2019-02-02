/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:49:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/02 18:33:34 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int	get_option(int ac, char **av, t_opt *opt, t_prgm *glob)
{
	int				c;
	unsigned int	option;

	option = 0;
	while ((c = ft_getopt(ac, av, OPTION)) != -1)
	{
		if (c == 0)
			return (0);
		else if (c < 0)
		{
			glob->optopt = -c;
			return ('?');
		}
		else if ((c == 'l' && option & LS_1) || (c == '1' && option & LS_L))
			option ^= LS_1 + LS_L;
		else if ((c == 'l' && option & LS_M) || (c == 'm' && option & LS_L))
			option ^= LS_M + LS_L;
		else if ((c == 'm' && option & LS_1) || (c == '1' && option & LS_M))
			option ^= LS_M + LS_1;
		else
			option |= opt[c];
	}
	return (option);
}

unsigned int		options(int ac, char **av, t_prgm *glob)
{
	t_opt		opt[127];

	opt['l'] = E_L;
	opt['1'] = E_1;
	opt['R'] = E_RR;
	opt['a'] = E_A;
	opt['t'] = E_T;
	opt['G'] = E_G;
	opt['m'] = E_M;
	opt['S'] = E_S;
	opt['r'] = E_R;
	opt['T'] = E_TT;
	return (get_option(ac, av, opt, glob));
}

void			get_color(t_prgm *glob, t_status *file)
{
	if (glob->option & LS_G)
	{
		if (S_ISDIR(file->info.st_mode))
			ft_strcpy(glob->color, DCLR);
		else if (S_ISLNK(file->info.st_mode))
			ft_strcpy(glob->color, LCLR);
		else if (S_ISFIFO(file->info.st_mode))
			ft_strcpy(glob->color, FCLR);
		else if (S_ISSOCK(file->info.st_mode))
			ft_strcpy(glob->color, SCLR);
		else if (S_ISCHR(file->info.st_mode))
			ft_strcpy(glob->color, CCLR);
		else if (S_ISBLK(file->info.st_mode))
			ft_strcpy(glob->color, DCLR);
		else if (file->info.st_mode & S_IXUSR\
			&& file->info.st_mode &S_IXGRP\
			&& file->info.st_mode & S_IXOTH)
			ft_strcpy(glob->color, XCLR);
		else
			ft_strcpy(glob->color, GREY);
	}
}
