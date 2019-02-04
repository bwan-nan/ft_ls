/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 22:08:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/02 22:37:19 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

void	time_format(t_prgm *glob, t_display *info, time_t timestamp)
{
	time_t		today;

	time(&today);
	if (glob->option & LS_TT)
	{
		info->time = 20;
		info->time2 = 0;
	}
	else if (today - timestamp > SIX_MONTHS
			|| timestamp - today > SIX_MONTHS)
	{
		info->time = 6;
		info->time2 = 4;
	}
	else 
	{
		info->time = 12;
		info->time2 = 0;
	}
}

void	print_device_line(t_prgm *glob, t_status *file, t_display *info)
{
	char	*full_date;

	full_date = ft_strdup(ctime(&file->info.st_mtime));
	ft_printf("%*s  %-*d %-*s  %-*s  %*d, %*d %s%.*s %s%s\033[0m"
			, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
			, info->pw_len, (getpwuid(file->info.st_uid))->pw_name
			, info->gr_len, (getgrgid(file->info.st_gid))->gr_name
			, info->maj_len, major(file->info.st_rdev)
			, info->min_len, minor(file->info.st_rdev)
			, info->time2 ? 1 : 0, " "
			, info->time,  full_date + 4
			, info->time2, full_date + 20
			, info->time2 ? 1 : 0, " "
			, glob->color, file->name);
	free(full_date);
}

void	print_regular_line(t_prgm *glob, t_status *file, t_display *info)
{
	char	*full_date;

	full_date = ft_strdup(ctime(&file->info.st_mtime));
	ft_printf("%-*s  %-*d %-*s  %-*s  %*d %.*s %.*s%.*s%.*s %s%s\033[0m"
			, info->ch_len, file->chmod, info->nlink, file->info.st_nlink
			, info->pw_len, (getpwuid(file->info.st_uid))->pw_name
			, info->gr_len, (getgrgid(file->info.st_gid))->gr_name
			, info->size, file->info.st_size
			, info->time, full_date + 4
			, info->time2 ? 1 : 0, " "
			, info->time2, full_date + 20
			, info->time2 ? 1 : 0, " "
			, glob->color, file->name);
	free(full_date);
}
