/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:14:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:59:15 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	stack_len(t_stack *stack)
{
	int	count;

	count = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}

t_stack	*new_entry(int value, t_stack *stack)
{
	t_stack	*entry;

	entry = malloc(sizeof(t_stack));
	if (!entry)
		return (NULL);
	entry->content = value;
	if (stack)
		entry->next = stack;
	else
		entry->next = NULL;
	return (entry);
}

t_stack	*remove_first(t_stack *stack)
{
	t_stack	*new;

	if (!stack)
		return (NULL);
	new = stack->next;
	free(stack);
	return (new);
}

void	remove_last(t_stack **stack)
{
	t_stack	*temp;

	if (!(*stack) || !((*stack)->next))
		return ;
	temp = *stack;
	while (temp->next->next)
		temp = temp->next;
	free(temp->next);
	temp->next = NULL;
}

void	free_stack(t_stack **to_free)
{
	t_stack	*temp;

	while (*to_free)
	{
		temp = (*to_free)->next;
		free((*to_free)->content);
		free(*to_free);
		*to_free = temp;
	}
}
