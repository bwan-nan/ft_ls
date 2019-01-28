/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:49:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/26 14:02:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned int	get_option(int ac, char **av, t_opt *opt)
{
	int c;
	unsigned int option;

	option = 0;
	while ((c = ft_getopt(ac, av, OPTION)) != -1)
	{
		if (c == 0)
			return (0);
		else if (c == '?')
			return ('?');
		else if ((c == 'l' && option & LS_1) || (c == '1' && option & LS_L))
			option ^= 3;
		else
			option |= opt[c];
	}
	return (option);
}

unsigned int	options(int ac, char **av)
{
	t_opt		opt[127];

	opt['l'] = E_L;
	opt['1'] = E_1;
	opt['R'] = E_R;
	opt['a'] = E_A;
	return (get_option(ac, av, opt));
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
			glob->home = ft_strsub(env[i], 5, ft_strlen(&env[i][3]));
		if (ft_strnequ(env[i], "LSCOLORS=", 8))
			glob->colors = ft_strsub(env[i], 9, ft_strlen(&env[i][4]));
		i++;
	}
	return (1);
}

void			tilde_replace(t_prgm *glob)
{
	t_list	*tmp;
	char	*holder;

	tmp = glob->args;
	while (tmp)
	{
		if(ft_strequ((char *)(tmp->data), "~"))
		{
			ft_memdel(&tmp->data);
			tmp->data = (void *)ft_strdup(glob->home);
		}
		else if (ft_strnequ((char *)(tmp->data), "~/", 2))
		{
			holder = NULL;
			ft_asprintf(&holder, "%s%s", glob->home, tmp + 2);
			ft_memdel(&tmp->data);
			tmp->data = (void *)holder;
		}
		tmp = tmp->next;
	}
}
