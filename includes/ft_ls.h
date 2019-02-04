/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/02 22:14:58 by bwan-nan         ###   ########.fr       */
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

# define OPTION		"1GRSTalmrt"
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

# define DIR_MAX	4096
# define SIX_MONTHS	15780000

# define GREY		"\033[0;37m"
# define DCLR		"\033[1;96m"
# define XCLR		"\033[31m"
# define CCLR		"\033[103;34m"
# define BCLR		"\033[46;34m"
# define LCLR		"\033[35m"
# define FCLR		"\033[33m"
# define SCLR		"\033[32m"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct winsize	t_winsize;

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
}						t_opt;

typedef struct			s_status
{
	t_stat				info;
	acl_t				acl;
	char				*path;
	char				*name;
	char				*chmod;
	t_list				*dirlist;
}						t_status;

typedef struct			s_prgm
{
	char				dir[DIR_MAX];
	char				*color;
	t_list				*args;
	int					args_count;
	unsigned int		option;
	char				optopt;
}						t_prgm;

typedef struct			s_display
{
	t_winsize			window;
	size_t				ch_len;
	size_t				width;
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

int						listalldir(t_prgm *glob, t_list *lst, t_status *tmp);
int						list_directory(t_prgm *glob, char *path);
int						list_files(t_prgm *glob);

void					error(t_prgm *glob, t_status *info);
void					long_output(t_list *files_list, t_prgm *glob);
void					basic_output(t_list *lst, t_prgm *glob);
void					list_output(t_list *files_list, t_prgm *glob);
void					commas_output(t_list *files_list, t_prgm *glob);

void					basic_padding(t_list *lst, t_display *info);
void					print_basic(t_list *lst, t_display *info);
void					print_commas(t_prgm *glob, t_list *files_list, t_display *info);
void					print_line(t_prgm *glob, t_status *file,\
						t_display *info);
void					long_padding(t_list *lst, t_display *info,\
						t_status *tmp, size_t len);

void					del_node(void **data);
void					generate_lists(t_prgm *glob, t_list **file,\
						t_list **dir);
int						create_list(DIR *current, char *path,
						t_list **files_list, t_prgm *glob);

unsigned int			options(int ac, char **av, t_prgm *glob);
unsigned int			get_env(char **env, t_prgm *glob);

void					sort_list(t_list **files_list, t_prgm *glob);

size_t					nbrlen(int nbr);
char					*getchmod(t_status *file);
void					get_color(t_prgm *glob, t_status *file);
void					init_display(t_display *info);
void					symbolic_link(t_status *file);
void					output_handler(t_list *files_list, t_prgm *glob);


void					time_format(t_prgm *glob, t_display *info, time_t timestamp);
void					print_device_line(t_prgm *glob, t_status *file, t_display *info);
void					print_regular_line(t_prgm *glob, t_status *file, t_display *info);
#endif
