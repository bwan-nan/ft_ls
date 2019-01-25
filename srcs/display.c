/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/25 15:36:21 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			long_output(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	size_t		nlink_max;
	size_t		size_max;
	size_t		total;

	nlink_max = 0;
	size_max = 0;
	total = 0;
	padding(files_list, &nlink_max, &size_max, &total);
	tmp = (t_status *)(files_list->data);
	if (!ft_strequ(glob->dir, ".") && glob->option & LS_RR)
		ft_printf("%s\n", glob->dir);
	ft_printf("total %d\n", total);
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		line_display(tmp, nlink_max, size_max);
		files_list = files_list->next;
	}
}

void			list_output(t_list *files_list, t_prgm *glob)
{
	if (!ft_strequ(glob->dir, ".") && glob->option & LS_RR)
		ft_printf("%s\n", glob->dir);
	while (files_list)
	{
		ft_printf("%s\n", ((t_status *)(files_list->data))->name);	
		files_list = files_list->next;
	}
}

void			basic_output(t_list *files_list, t_prgm *glob)
{
	t_status 	*tmp;
	t_winsize	window;
	size_t		total;
	size_t		width;
	size_t		printed;

	total = 0;
	printed = 0;
	width = basic_padding(files_list, &total);
	ioctl(0, TIOCGWINSZ, &window);
	if (!ft_strequ(glob->dir, ".") && glob->option & LS_RR)
		ft_printf("%s\n", glob->dir);
	while (total > window.ws_col)
		total = total / 2;	
	while (files_list)
	{
		tmp = ((t_status *)(files_list)->data);
		printed += ft_printf("%-*s", width, tmp->name);	
		if (printed > total)
		{
			ft_putchar('\n');
			printed = 0;
		}
		files_list = files_list->next;
	}
	ft_putchar('\n');
}

void			output_handler(t_list *files_list, t_prgm *glob)
{
	if (glob->option & LS_L)
		long_output(files_list, glob);
	else if (glob->option & LS_1)
		list_output(files_list, glob);
	else
		basic_output(files_list, glob);
}
