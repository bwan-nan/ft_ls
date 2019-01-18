/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/18 01:40:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*create_lst(DIR *current, char *path)
{
	t_status	file;
	t_list		*lst;
	char		*holder;

	lst = NULL;
	while ((file.file = readdir(current)))
	{
		file.path = ft_strjoin(path, "/");		
		holder = ft_strjoin(file.path, file.file->d_name);	
		stat(holder, &file.info);
		ft_strdel(&file.path);
		file.path = holder;
		ft_lstaddback(&lst, ft_lstnew(&file, sizeof(t_status)));
	}
	return (lst);
}

void	printlst(t_list *lst)
{
	t_status	*tmp;

	while (lst)
	{
		tmp = ((t_status *)lst->data);
		ft_printf("%s\n",tmp->file->d_name);
		lst = lst->next;
	}
}

int		backtrack(t_list *lst)
{
	t_status	*tmp;
	char		*holder;

	while (lst)
	{
		tmp = (t_status *)(lst->data);
		if (S_ISDIR(tmp->info.st_mode) && !ft_strequ(tmp->file->d_name , ".") 
			&& 	!ft_strequ(tmp->file->d_name , "..") && *tmp->file->d_name != '.')
		{
			holder = tmp->path;
			tmp->dirlst = create_lst(opendir(tmp->path), tmp->path);
			printlst(tmp->dirlst);
			backtrack (tmp->dirlst);
			ft_lstdel(&(tmp->dirlst), NULL);
			ft_strdel(&holder);
		}
		lst = lst->next;
	}
	return (0);
}

int		ft_ls(void)
{
	DIR 		*current;
	t_list		*lst;

	current = opendir (".");
	lst = create_lst(current, ".");
	printlst(lst);
	backtrack(lst);	
	return (1);
}
