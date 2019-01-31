/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:50:07 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/31 19:08:27 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_strrchr_index(const char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (--i)
		if (str[i] == c)
			return (--i) ;
	return (0);
}
