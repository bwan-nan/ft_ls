/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:49:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/31 13:14:14 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned int	get_option(int ac, char **av, t_opt *opt, t_prgm *glob)
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

unsigned int	options(int ac, char **av, t_prgm *glob)
{
	t_opt		opt[127];

	opt['l'] = E_L;
	opt['1'] = E_1;
	opt['R'] = E_RR;
	opt['a'] = E_A;
	opt['t'] = E_T;
	opt['u'] = E_U;
	opt['m'] = E_M;
	opt['S'] = E_S;
	opt['r'] = E_R;
	opt['T'] = E_TT;
	return (get_option(ac, av, opt, glob));
}

unsigned int	get_env(char **env, t_prgm *glob)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], "PWD=", 4))
			glob->pwd = ft_strsub(env[i], 4, ft_strlen(env[i]));
		if (ft_strnequ(env[i], "HOME=", 5))
			glob->home = ft_strsub(env[i], 5, ft_strlen(&env[i][3]) - 1);
		if (ft_strnequ(env[i], "LSCOLORS=", 8))
			glob->colors = ft_strsub(env[i], 9, ft_strlen(&env[i][4]));
		i++;
	}
	return (1);
}
