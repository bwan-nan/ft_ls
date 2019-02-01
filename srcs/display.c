/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 17:18:53 by cempassi         ###   ########.fr       */
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
}

void	long_output(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	t_display	info;

	init_display(&info);
	long_padding(files_list, &info);
	tmp = (t_status *)(files_list->data);
	if (glob->args_count)
		ft_printf("%s:\n", glob->dir);
	ft_printf("total %d\n", info.total);
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		print_line(glob, tmp, &info);
		files_list = files_list->next;
	}
	glob->args_count = 2;
}

void	list_output(t_list *files_list, t_prgm *glob)
{
	if (glob->args_count)
		ft_printf("%s:\n", glob->dir);
	while (files_list)
	{
		ft_printf("%s\n", ((t_status *)(files_list->data))->name);
		files_list = files_list->next;
	}
	glob->args_count = 2;
}

void	basic_output(t_list *lst, t_prgm *glob)
{
	t_status	*tmp;
	t_display	info;

	info.total = 0;
	info.printed = 0;
	info.width = 15;
	basic_padding(lst, &info);
	tmp = (t_status *)lst->data;
	if (glob->args_count)
		ft_printf("%s:\n", glob->dir);
	print_basic(lst, &info);
	glob->args_count = 2;
}

void	commas_output(t_list *files_list, t_prgm *glob)
{
	t_display	info;
	size_t		len;

	info.total = 0;
	info.width = 0;
	info.printed = 0;
	if (files_list)
	{
		ioctl(0, TIOCGWINSZ, &info.window);
		if (!ft_strequ(glob->dir, "."))
			ft_printf("%s:\n", glob->dir);
		while (files_list)
		{
			if (files_list->next)
				len = ft_strlen(((t_status *)(files_list->next->data))->name);
			print_comma(files_list, &info);
			files_list = files_list->next;
		}
	}
}
