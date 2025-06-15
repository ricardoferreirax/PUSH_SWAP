/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:32:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:46:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_stack *new_element(int *content)
{
	t_stack *new_element;

	new_element = (t_stack *)malloc(sizeof(t_stack));
	if (!new_element)
		return (NULL);
	new_element->next = NULL;
	new_element->content = content;
	return (new_element);
}

void stack_add_back(t_stack *element, t_stack **stack)
{
	t_stack *tmp;

	if (!element || !stack)
		return ;
	if (!(*stack))
	{
		*stack = element;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
}

int is_numeric(char *str)
{
	int idx;

	idx = 0;
	while (str[idx])
	{
		if ((str[idx] < '0' || str[idx] > '9') 
			&& str[idx] != '-' && str[idx] != '+')
			return (0);
		idx++;
	}
	return (1);
}

int ft_atoi(const char *str)
{
	int idx;
	int sign;
	int result;

	idx = 0;
	sign = 1;
	result = 0;
	while (str[idx] == ' ' || (str[idx] >= 9 && str[idx] <= 13))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		result = result * 10 + (str[idx] - '0');
		idx++;
	}
	return (result * sign);
}

long int big_atoi(char *str)
{
	int idx;
	int sign;
	long int result;

	idx = 0;
	sign = 1;
	result = 0;
	while (str[idx] == ' ' || (str[idx] >= 9 && str[idx] <= 13))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		result = result * 10 + (str[idx] - '0');
		idx++;
	}
	return (result * sign);
}
