/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:56:08 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/08 10:33:11 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_shape(t_shape *s, int rows, int cols)
{
	s->p = (t_coord *)malloc(sizeof(t_coord) * rows * cols);
}

void	compose_shape(t_token *t, int row, int col)
{
	t_shape	*s;

	s = t->shape;
	if (s->cnt == 0)
	{
		s->p[0].row = 0;
		s->p[0].col = 0;
		t->corner.row = -row;
		t->corner.col = -col;
	}
	else
	{
		s->p[s->cnt].row = row - s->p[0].row;
		s->p[s->cnt].col = col - s->p[0].col;
	}
	s->cnt++;
}

void	calc_shape_bounds(t_shape *s)
{
	t_coord	min;
	t_coord	max;
	int		i;

	min.col = 1000;
	min.row = 1000;
	max.col = -1000;
	max.row = -1000;
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
