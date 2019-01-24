/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/24 17:28:38 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS


# include "ft_printf.h"
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

# define OPTIONS "l1RratG"

# define LS_L		1
# define LS_1		2
# define LS_R		4
# define LS_LOW_R	8
# define LS_A		16
# define LS_T		32
# define LS_G		64

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;
typedef struct group		t_group;

typedef struct				s_status
{
	char					*path;
	char					*name;
	ino_t					inode;
	t_list					*dirlist;
	t_stat					info;
	t_group					group;
}							t_status;

typedef struct				s_prgm
{
	unsigned int			options;
	char					*pwd;
	char					**arg;
}							t_prgm;

int		ft_ls(t_prgm *glob);
void	print_list(t_list *files_list);
void	get_the_right_size(t_list *files_list, int *tab);
void	merge_sort(t_list **source, int (*cmp)(void *, void *));
int		parsing(int ac, char **av, unsigned int *flags);

int		sort_ascii(void *a, void *b);

void	del_node(void **data);
int		create_list(DIR *current, char *path, t_list **files_list, t_prgm *glob);
#endif
