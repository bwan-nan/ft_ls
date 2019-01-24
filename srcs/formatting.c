/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:42:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/24 21:58:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	nbrlen(int nbr)
{
	if (nbr >= 1000000000) 
		return (10);
    if (nbr >= 100000000)  
		return (9);
    if (nbr >= 10000000)   
		return (8);
    if (nbr >= 1000000)    
		return (7);
    if (nbr >= 100000)     
		return (6);
    if (nbr >= 10000)      
		return (5);
    if (nbr >= 1000)       
		return (4);
    if (nbr >= 100)        
		return (3);
    if (nbr >= 10)         
		return (2);
    return (1);
}

void			padding(t_list *lst, size_t *nlink, size_t *size, size_t *total)
{
	t_status	*tmp;
	size_t		len;

	while (lst)
	{
		tmp = (t_status *)(lst->data);
		if ((len = nbrlen(tmp->info.st_nlink)) > *nlink)
			*nlink = len;
		if ((len = nbrlen(tmp->info.st_size)) > *size)
			*size = len;
		*total += tmp->info.st_blocks;
		lst = lst->next;
	}
}
