/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:05:34 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/23 18:04:06 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			partition(t_list *head, t_list **front, t_list **back)
{
	t_list		*fast;
	t_list		*slow;

	if (!head || !head->next)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

static t_list		*merge_lists(t_list **a, t_list **b, int (*cmp)(void *, void *))
{
	t_list		*merged_list;
	t_status	*tmp1;
	t_status	*tmp2;

	merged_list = NULL;
	if (*a == NULL)
		return (*b);
	else if (*b == NULL)
		return (*a);
	tmp1 = (t_status *)((*a)->data);
	tmp2 = (t_status *)((*b)->data);
	if (cmp(tmp1, tmp2) <= 0)
	{
		merged_list = *a;
		merged_list->next = merged_list(a, b->next);
	}
	return (merged_list);
}	

int					merge_sort(t_list **files_list, int (*cmp)(void *, void *))
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *files_lists;
	if (!head || !head->next)
		return (0);
	partition(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*files_list = merge_lists(a, b, cmp);
}
