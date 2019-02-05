/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/05 17:09:33 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf.h"
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>
# include <uuid/uuid.h>
# include <unistd.h>

# define OPTION		"1CGRST@aflmrtx"
# define LS_L		1
# define LS_1		2
# define LS_RR		4
# define LS_A		8
# define LS_T		16
# define LS_G		32
# define LS_M		64
# define LS_S		128
# define LS_R		256
# define LS_TT		512
# define LS_F		1024
# define LS_X		2048
# define LS_C		4096
# define LS_AR		8192

# define BLACK		30
# define RED		31
# define GREEN		32
# define YELLOW		33
# define BLUE		34
# define MAGENTA	35
# define CYAN		36
# define WHITE		37
# define NC			0

# define MAJDIFF	65
# define MINDIFF	97

# define BUF		255
# define DIR_MAX	4096
# define SIX_MONTHS	15780000

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct winsize	t_winsize;
typedef struct group	t_group;

typedef enum			e_opt
{
	E_L = LS_L,
	E_1 = LS_1,
	E_RR = LS_RR,
	E_A = LS_A,
	E_T = LS_T,
	E_G = LS_G,
	E_M = LS_M,
	E_S = LS_S,
	E_R = LS_R,
	E_TT = LS_TT,
	E_F = LS_F,
	E_X = LS_X,
	E_C = LS_C,
	E_AR = LS_AR
}						t_opt;

typedef struct			s_status
{
	t_stat				info;
	acl_t				acl;
	char				*path;
	char				*name;
	char				*chmod;
	char				*grp;
	char				*pwd;
	char				*xattr;
	t_list				*dirlist;
	ssize_t				xattr_len;
}						t_status;

typedef struct			s_display
{
	size_t				ch_len;
	size_t				width;
	size_t				lst_len;
	size_t				lines;
	size_t				mod;
	size_t				total;
	size_t				printed;
	size_t				nlink;
	size_t				size;
	size_t				pw_len;
	size_t				gr_len;
	size_t				maj_len;
	size_t				min_len;
	size_t				time;
	size_t				time2;
}						t_display;

typedef struct			s_prgm
{
	t_winsize			window;
	t_status			tmp;
	t_display			info;
	char				dir[DIR_MAX];
	char				*ls_colors;
	t_list				*args;
	int					args_count;
	void				*holder;
	unsigned int		option;
	char				optopt;
	char				*colors[13];
}						t_prgm;

int						listalldir(t_prgm *glob, t_list *lst, t_status *tmp);
int						list_directory(t_prgm *glob, char *path);
int						list_files(t_prgm *glob);

void					error(t_prgm *glob, t_status *info);
void					long_output(t_prgm *glob, t_list *lst);
void					basic_output(t_prgm *glob, t_list *lst);
void					list_output(t_prgm *glob, t_list *lst);
void					commas_output(t_prgm *glob, t_list *lst);

void					print_basic_line(t_prgm *glob, t_list *lst,\
						t_display *info);
void					print_basic_col(t_prgm *glob, t_list *lst,\
						t_display *info, char *colo);
void					basic_padding(t_prgm *glob, t_list *lst,\
						t_display *info);
void					print_commas(t_prgm *glob, t_list *files_list,\
						t_display *info);
void					print_line(t_prgm *glob, t_status *file,\
						t_display *info);
void					long_padding(t_list *lst, t_display *info,\
						t_status *tmp, size_t len);

void					del_node(void **data);
void					generate_lists(t_prgm *glob, t_list *args,\
						t_list **file, t_list **dir);
int						create_list(DIR *current, char *path,
						t_list **files_list, t_prgm *glob);

unsigned int			options(int ac, char **av, t_prgm *glob);
unsigned int			get_env(char **env, t_prgm *glob);
void					init_colors(t_prgm *glob);

void					sort_list(t_list **files_list, t_prgm *glob);

size_t					nbrlen(int nbr);
char					*getchmod(t_status *file, char *buffer);
void					get_color(t_prgm *glob, t_status *file);
char					*display_color(t_prgm *glob, mode_t mode);
void					init_display(t_display *info);
void					symbolic_link(t_status *file);
void					output_handler(t_prgm *glob, t_list *lst);

void					print_xattr(t_status *file, char *xattr);
void					time_format(t_prgm *glob, t_display *info,\
						time_t timestamp);
void					print_long_device(t_prgm *glob, t_status *file,
						t_display *info);
void					print_long_regular(t_prgm *glob, t_status *file,\
						t_display *info);
#endif
