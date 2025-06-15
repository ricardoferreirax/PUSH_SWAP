/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheapest_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:43:49 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:04 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int cheapest_move(int value, t_stack *stack_a, t_stack *stack_b)
{
    int cost;
    int rot_a;
    int rot_b;
    int strategy;

    strategy = 0;
    rot_a = find_position_in_b(value, stack_a);
    rot_b = find_place_in_a(value, stack_b);
    cost = cost_both_down(rot_a, rot_b, stack_len(stack_b), stack_len(stack_a));
    if (cost > cost_both_up(rot_a, rot_b))
    {
        strategy = 1;
        cost = cost_both_up(rot_a, rot_b);
    }
    if (cost > cost_a_up_b_down(rot_a, rot_b, stack_len(stack_a)))
    {
        strategy = 2;
        cost = cost_a_up_b_down(rot_a, rot_b, stack_len(stack_a));
    }
    if (cost > cost_a_down_b_up(rot_a, rot_b, stack_len(stack_b)))
        strategy = 3;
    return (strategy);
}
