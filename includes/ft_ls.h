/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/21 18:00:41 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;
typedef struct group		t_group;

typedef struct				s_status
{
	char					*path;
	t_dirent				*dirent;
	t_list					*dirlist;
	t_stat					info;
	t_group					group;
}							t_status;

int		ft_ls(void);
void	print_list(t_list *files_list);
void	get_the_right_size(t_list *files_list, int *tab);

#endif
