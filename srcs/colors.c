/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 21:14:44 by cedricmpa         #+#    #+#             */
/*   Updated: 2019/02/04 19:30:13 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		set_colors(t_prgm *glob, char *colors, char *values, char i)
{
	int			id[2];
	char		bold;

	if (*colors == '\0')
		return ;
	bold = 0;
	if (colors[0] >= 'a' && colors[0] <= 'h')
		id[0] = *colors - 97;
	else if (colors[0] >= 'A' && colors[0] <= 'H' && (bold = 1))
		id[0] = colors[0] - 65;
	else
		id[0] = 8;

	if (colors[1] >= 'a' && colors[1] <= 'h')
		id[1] = colors[1] - 97;
	else if (colors[1] >= 'A' && colors[1] <= 'H')
		id[1] = colors[1] - 65;
	else
		id[1] = 8;
	ft_asprintf(glob->colors + i, "\x1b[%d;%d;%dm"
			, bold, values[id[0]]
			, (id[1] = values[id[1]]) + 10 == 10 ? values[id[0]] : id[1] + 10);
	return (set_colors(glob, colors + 2, values, ++i));
}

void		init_colors(t_prgm *glob)
{
	char	colors[9];
	char	bold;

	bold = 0;
	colors[0] = BLACK;
	colors[1] = RED;
	colors[2] = GREEN;
	colors[3] = YELLOW;
	colors[4] = BLUE;
	colors[5] = MAGENTA;
	colors[6] = CYAN;
	colors[7] = WHITE;
	colors[8] = NC;
	glob->colors[11] = ft_strdup("\x1b[0m");
	glob->colors[12] = NULL;
	set_colors(glob, glob->ls_colors, colors, 0);
}

char		*special_color(t_prgm *glob, mode_t mode)
{
	if (S_IXUSR & mode || S_IXGRP & mode || S_IXOTH & mode)
	{
		if (S_ISUID & mode)
			return (glob->colors[7]);
		if (S_ISGID & mode)
			return (glob->colors[8]);
		else
			return (glob->colors[4]);
	}
	else if (S_ISFIFO(mode))
			return (glob->colors[3]);
	else if (S_ISBLK(mode))
			return (glob->colors[5]);
	else if (S_ISCHR(mode))
			return (glob->colors[6]);
	else
			return (glob->colors[11]);

}

char		*display_color(t_prgm *glob, mode_t mode)
{
	if (S_ISDIR(mode))
	{
		if (S_IWOTH & mode && S_ISVTX & mode)
			return (glob->colors[9]);
		else if (S_IWOTH & mode && !(S_ISVTX & mode))
			return (glob->colors[10]);
		else
			return (glob->colors[0]);
	}
	else if (S_ISSOCK(mode))
			return (glob->colors[2]);
	else if (S_ISLNK(mode))
			return (glob->colors[1]);
	else
		return (special_color(glob, mode));
}
