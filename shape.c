/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:56:08 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/09 16:40:40 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_shape(t_shape *s, int rows, int cols)
{
	s->p = (t_coord *)malloc(sizeof(t_coord) * rows * cols);
	s->cnt = 0;
}

void	compose_shape(t_token *t, int row, int col)
{
	t_shape	*s;

	s = t->shape;
	if (s->cnt == 0)
	{
		set_coord(&(s->p[0]), 0, 0);
		t->corner.row = -row;
		t->corner.col = -col;
	}
	else
		set_coord(&(s->p[s->cnt]), row + t->corner.row,
			col + t->corner.col);
	s->cnt++;
}

void	calc_shape_bounds(t_shape *s)
{
	t_coord	min;
	t_coord	max;
	int		i;

	set_coord(&min, 100000, 100000);
	set_coord(&max, -100000, -100000);
	i = 0;
	while (i < s->cnt)
	{
		if (s->p[i].row > max.row)
			max.row = s->p[i].row;
		if (s->p[i].row < min.row)
			min.row = s->p[i].row;
		if (s->p[i].col > max.col)
			max.col = s->p[i].col;
		if (s->p[i].col < min.col)
			min.col = s->p[i].col;
		i++;
	}
	s->min = min;
	s->max = max;
}
