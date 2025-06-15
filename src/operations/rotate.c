/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:38:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	rotate(t_stack **stack)
{
	int		temp;
	t_stack	*current;

	if (!(*stack) || !(*stack)->next)
		return ;
	temp = (*stack)->content;
	current = *stack;
	while (current->next)
	{
		current->content = current->next->content;
		current = current->next;
	}
	if (current->next == NULL)
		current->content = temp;
}
