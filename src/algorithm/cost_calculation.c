/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:47:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:47:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// custo de rodar ambas para cima (rotate)
int cost_both_up(int rot_a, int rot_b)
{
    int cost;

	cost = 0;
    while (rot_a > 0 && rot_b > 0)
    {
        rot_a--;
        rot_b--;
        cost++;
    }
    while (rot_a != 0)
    {
        rot_a--;
        cost++;
    }
    while (rot_b != 0)
    {
        rot_b--;
        cost++;
    }
    return cost;
}

// custo de rodar ambas para baixo (reverse rotate)
int cost_both_down(int rot_a, int rot_b, int size_a, int size_b)
{
    int cost;

    cost = 0;
    while (rot_a < size_b && rot_b < size_a)
    {
        rot_a++;
        rot_b++;
        cost++;
    }
    while (rot_a < size_b)
    {
        rot_a++;
        cost++;
    }
    while (rot_b < size_a)
    {
        rot_b++;
        cost++;
    }
    return cost;
}

// custo de rodar A para cima + rodar B para baixo
int cost_a_up_b_down(int rot_a, int rot_b, int size_b)
{
    int cost;

    cost = 0;
    while (rot_a != size_b)
    {
        rot_a++;
        cost++;
    }
    while (rot_b != 0)
    {
        rot_b--;
        cost++;
    }
    return cost;
}

// custo de rodar A para baixo + rodar B para cima
int cost_a_down_b_up(int rot_a, int rot_b, int size_a)
{
    int cost;

    cost = 0;
    while (rot_a != 0)
    {
        rot_a--;
        cost++;
    }
    while (rot_b != size_a)
    {
        rot_b++;
        cost++;
    }
    return cost;
}

int calculate_min_cost(int value, t_stack *stack_b, t_stack *stack_a)
{
    int cost;
    int rot_b;
    int rot_a;

    rot_b = find_position_in_b(value, stack_a);
    rot_a = find_place_in_a(value, stack_b);
    cost = cost_both_down(rot_b, rot_a, stack_len(stack_b), stack_len(stack_a));
    if (cost > cost_both_up(rot_b, rot_a))
        cost = cost_both_up(rot_b, rot_a);
    if (cost > cost_a_up_b_down(rot_b, rot_a, stack_len(stack_a)))
        cost = cost_a_up_b_down(rot_b, rot_a, stack_len(stack_a));
    if (cost > cost_a_down_b_up(rot_b, rot_a, stack_len(stack_b)))
        cost = cost_a_down_b_up(rot_b, rot_a, stack_len(stack_b));
    return (cost + 1);
}
