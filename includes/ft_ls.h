/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/25 16:57:19 by bwan-nan         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <uuid/uuid.h>

# define OPTION		"l1Ratuf"
# define LS_L		1
# define LS_1		2
# define LS_RR		4
# define LS_A		8
# define LS_T		16
# define LS_U		32
# define LS_F		64

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;
typedef struct group		t_group;
typedef struct winsize		t_winsize;

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
	unsigned int			option;
	char					*pwd;
	char					*home;
	char					**args;
	char					dir[255];
}							t_prgm;


int		list_directory(t_prgm *glob, char *path);
int		list_files(t_prgm *glob, char *path);

void	output_handler(t_list *files_list, t_prgm *glob);
void	long_output(t_list *files_list, t_prgm *glob);
void	line_display(t_status *file, size_t nlink, size_t size);
void	padding(t_list *lst, size_t *nlink, size_t *size, size_t *total);
int		basic_padding(t_list *lst, size_t *total);

int		name_filter(void *data, void *filter);
void	del_node(void **data);
int		create_list(DIR *current, char *path, t_list **files_list,\
		t_prgm *glob);

void	merge_sort(t_list **source, int (*cmp)(void *, void *));
int		sort_ascii(void *a, void *b);
int		sort_time_modified(void *a, void *b);
int		sort_last_access(void *a, void *b);
#endif
