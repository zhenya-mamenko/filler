/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:46:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/08 20:03:14 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coord	find_place(t_filler *f)
{
	t_coord	min;
	t_coord	max;
	t_coord	res;
	int		tmp;
	int		best;

	tmp = f->t.shape->max.row - f->t.shape->min.row;
	min.row = f->b.min.row > tmp ? f->b.min.row - tmp : 0;
	max.row = f->b.max.row + tmp < f->b.rows ? f->b.max.row + tmp : f->b.rows;
	tmp = f->t.shape->max.col - f->t.shape->min.col;
	min.col = f->b.min.col > tmp ? f->b.min.col - tmp : 0;
	max.col = f->b.max.col + tmp < f->b.cols ? f->b.max.col + tmp : f->b.cols;
	best = 0;
	while (min.row <= max.row)
	{
		tmp = min.col - 1;
		while (++tmp <= max.col)
		{
		}
		min.row++;
	}
	return (res);
}
