/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:39:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:54 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	r_rotate(t_stack **stack)
{
	t_stack	*adress_of_last;
	t_stack	*temp;

	if (!(*stack) || !(*stack)->next)
		return ;
	temp = *stack;
	while (temp->next->next)
		temp = temp->next;
	adress_of_last = temp->next;
	temp->next = NULL;
	adress_of_last->next = *stack;
	*stack = adress_of_last;
}
