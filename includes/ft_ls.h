/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/25 16:47:23 by cempassi         ###   ########.fr       */
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
# define OPTION "1lRa"
# define DIR_MAX 255
# define LS_L 1
# define LS_1 2
# define LS_RR 4
# define LS_A 8

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
	char					dir[DIR_MAX];
}							t_prgm;


int		list_directory(t_prgm *glob, char *path);
int		list_files(t_prgm *glob, char *path);

void	output_handler(t_list *files_list, t_prgm *glob);
void	long_output(t_list *files_list, t_prgm *glob);
void	line_display(t_status *file, size_t nlink, size_t size);
void	padding(t_list *lst, size_t *nlink, size_t *size, size_t *total);
int		basic_padding(t_list *lst, size_t *total);

int		file_filter(void *data, void *filter);
int		dir_filter(void *data, void *filter);
void	del_node(void **data);
int		create_list(DIR *current, char *path, t_list **files_list,\
		t_prgm *glob);
#endif
