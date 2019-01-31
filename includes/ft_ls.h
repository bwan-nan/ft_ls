/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/01 00:05:36 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

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
# include <unistd.h>

# define OPTION		"1RSTalmrtu"
# define LS_L		1
# define LS_1		2
# define LS_RR		4
# define LS_A		8
# define LS_T		16
# define LS_U		32
# define LS_M		64
# define LS_S		128
# define LS_R		256
# define LS_TT		512

# define DIR_MAX	255

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct winsize	t_winsize;

typedef enum			e_opt
{
	E_L = LS_L,
	E_1 = LS_1,
	E_RR = LS_RR,
	E_A = LS_A,
	E_T = LS_T,
	E_U = LS_U,
	E_M = LS_M,
	E_S = LS_S,
	E_R = LS_R,
	E_TT = LS_TT,
}						t_opt;

typedef struct			s_status
{
	char				*path;
	char				*name;
	char				*dir;
	t_list				*dirlist;
	t_stat				info;
	t_group				group;
}						t_status;

typedef struct			s_prgm
{
	unsigned int		option;
	char				optopt;
	char				*pwd;
	char				*home;
	char				*colors;
	t_list				*args;
	int				args_count;
	char				dir[DIR_MAX];
}						t_prgm;

typedef struct			s_display
{
	size_t				width;
	size_t				total;
	size_t				printed;
	t_winsize			window;
}						t_display;

void					listonedir(t_prgm *glob, DIR *current,\
						t_status *tmp, int flag);
int						listalldir(t_prgm *glob,\
						t_list *files_list, t_status *tmp);
int						list_directory(t_prgm *glob, char *path);
int						list_files(t_prgm *glob);

void					error(t_status *info);
void					output_handler(t_list *files_list, t_prgm *glob);
void					long_output(t_list *files_list, t_prgm *glob);
void					line_display(t_prgm *glob, t_status *file,\
						size_t nlink, size_t size);
void					basic_padding(t_list *lst, t_display *info);
void					basic_default(t_prgm *glob, t_list *lst,\
						t_display *info);
void					padding(t_list *lst, size_t *nlink, size_t *size,\
						size_t *total);

void					del_node(void **data);
int						create_list(DIR *current, char *path,
						t_list **files_list, t_prgm *glob);

unsigned int			basic(char c, unsigned char option);
unsigned int			options(int ac, char **av, t_prgm *glob);
unsigned int			get_env(char **env, t_prgm *glob);
t_list					*dir_node(t_prgm *glob, char *path, char *name,\
						t_status *file);

void					merge_sort(t_list **source, int (*cmp)(void *, void *));
void					lst_rev(t_prgm **alst);
void					sort_list(t_list **files_list, t_prgm *glob);
int						sort_ascii(void *a, void *b);
int						sort_time_modified(void *a, void *b);
int						sort_last_access(void *a, void *b);
int						sort_by_size(void *a, void *b);

void					list_with_commas(t_list *files_list, t_prgm *glob);


int					ft_strrchr_index(const char *str, char c);
int					ft_getargscount(int ac, char **av);
#endif
