/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/11 16:00:18 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	error(t_prgm *glob, t_status *info)
{
	char *error;

	error = NULL;
	if (glob->args_count)
		ft_printf("%s:\n", &glob->dir[*glob->dir == '.' && glob->args ? 2 : 0]);
	if (*info->path == '.')
		ft_asprintf(&error, "ft_ls: %s", info->name);
	else
		ft_asprintf(&error, "ft_ls: %s", info->path);
	perror(error);
	ft_strdel(&error);
	ft_strdel(&info->path);
	ft_strdel(&info->name);
	glob->error = 1;
}

void	long_output(t_prgm *glob, t_list *lst)
{
	t_status	*tmp;

	init_display(&glob->info);
	if (glob->args_count)
		ft_printf("%s:\n", glob->dir);
	if (!lst)
		return ;
	long_padding(lst, &glob->info, NULL, 0);
	if (glob->args_count)
		ft_printf("total %d\n", glob->info.total);
	while (lst)
	{
		tmp = (t_status *)(lst->data);
		print_line(glob, tmp, &glob->info);
		ft_putchar('\n');
		lst = lst->next;
	}
	glob->args_count = 2;
}

void	list_output(t_prgm *glob, t_list *lst)
{
	char		*col;
	t_status	*tmp;

	if (glob->args_count)
		ft_printf("%s:\n", glob->dir);
	col = NULL;
	while (lst)
	{
		tmp = (t_status *)lst->data;
		if (glob->option & LS_G)
			col = display_color(glob, tmp->info.st_mode);
		ft_printf("%@s\n", col, tmp->name);
		lst = lst->next;
	}
	glob->args_count = 2;
}

void	basic_output(t_prgm *glob, t_list *lst)
{
	t_status	*tmp;

	init_display(&glob->info);
	if (glob->args_count)
		ft_printf("%s:\n", glob->dir);
	if (!lst)
		return ;
	basic_padding(glob, lst, &glob->info);
	tmp = (t_status *)lst->data;
	if (glob->option & LS_X)
		print_basic_line(glob, lst, &glob->info);
	else if (glob->info.total && glob->info.lst_len)
	{
		if (glob->info.total && glob->info.lst_len)
		{
			glob->info.lines = glob->info.lst_len / glob->info.total;
			glob->info.mod = glob->info.lst_len % glob->info.total ? 1 : 0;
		}
		print_basic_col(glob, lst, &glob->info, NULL);
	}
	glob->args_count = 2;
	ft_putchar('\n');
}

void	commas_output(t_prgm *glob, t_list *lst)
{
	t_status	*next;

	init_display(&glob->info);
	if (lst)
	{
		if (glob->args_count)
			ft_printf("%s:\n", glob->dir);
		while (lst)
		{
			if (lst->next && (next = (t_status *)(lst->next->data)))
				glob->info.size = ft_strlen((char *)next->name);
			print_commas(glob, lst, &glob->info);
			lst = lst->next;
		}
	}
	glob->args_count = 2;
}
