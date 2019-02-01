/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:01:52 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 15:36:19 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** option -m list files separated by commas
*/

static void		print_comma(t_list *files_list, t_display *info, size_t len)
{
	t_status	*tmp;

	tmp = (t_status *)(files_list->data);
	if (files_list->next)
	{
		info->printed += ft_printf("%s, ", tmp->name);
		if (info->printed + 2 + len > info->window.ws_col)
		{
			ft_putchar('\n');
			info->printed = 0;
		}
	}
	else
		info->printed += ft_printf("%s\n", tmp->name);
}

void			list_with_commas(t_list *files_list, t_prgm *glob)
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
			ft_printf("%s:\n", &glob->dir[*glob->dir == '.' ? 2 : 0]);
		while (files_list)
		{
			if (files_list->next)
				len = ft_strlen(((t_status *)(files_list->next->data))->name);
			print_comma(files_list, &info, len);
			files_list = files_list->next;
		}
	}
}
