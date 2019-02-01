/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 14:47:52 by cempassi         ###   ########.fr       */
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

void	init_display(t_display *info)
{
	info->width = 15;
	info->total = 0;
	info->printed = 0;
	info->nlink = 0;
	info->size = 0;
	info->pw_len = 0;
	info->gr_len = 0;
}

void	long_output(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	t_display	info;

	init_display(&info);
	padding(files_list, &info);
	tmp = (t_status *)(files_list->data);
	if (glob->args_count)
		ft_printf("%s:\n", &glob->dir[*glob->dir == '.' && glob->args ? 2 : 0]);
	ft_printf("total %d\n", info.total);
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		line_display(glob, tmp, &info);
		files_list = files_list->next;
	}
	glob->args_count = 1;
}

void	list_output(t_list *files_list, t_prgm *glob)
{
	if (glob->args_count)
		ft_printf("%s:\n", &glob->dir[*glob->dir == '.' && glob->args ? 2 : 0]);
	while (files_list)
	{
		ft_printf("%s\n", ((t_status *)(files_list->data))->name);
		files_list = files_list->next;
	}
	glob->args_count = 1;
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
		ft_printf("%s:\n", &glob->dir[*glob->dir == '.' && glob->args ? 2 : 0]);
	basic_default(glob, lst, &info);
	glob->args_count = 1;
}

void	output_handler(t_list *files_list, t_prgm *glob)
{
	if (files_list)
	{
		if (glob->option & LS_L)
			long_output(files_list, glob);
		else if (glob->option & LS_1)
			list_output(files_list, glob);
		else if (glob->option & LS_M)
			list_with_commas(files_list, glob);
		else
		{
			basic_output(files_list, glob);
		}
	}
}
