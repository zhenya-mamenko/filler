/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:46:40 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/09 15:06:20 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_coord(t_filler *f, t_coord p, t_coord sp)
{
	if (p.col + sp.col < 0 || p.row + sp.row < 0)
		return (-1);
	if (p.col + sp.col >= f->b.cols || p.row + sp.row >= f->b.rows)
		return (-1);
	return (0);
}

static void	try_place(t_filler *f, t_coord p, int *best)
{
	int		i;
	int		cnt;
	int		result;
	t_cell	c;
	t_coord	sp;

	result = 0;
	cnt = 0;
	i = -1;
	while (++i < f->t.shape->cnt)
	{
		sp = f->t.shape->p[i];
		if (check_coord(f, p, sp) == -1)
			return ;
		c = f->b.cells[p.row + sp.row][p.col + sp.col];
		result += c.weight;
		if (result < -100 || (cnt += (c.v == f->p.c ? 1 : 0)) > 1)
			return ;
	}
	if (*best >= result || cnt == 0)
		return ;
	*best = result;
	f->t.shape->best_place = p;
}

int			find_place(t_filler *f)
{
	t_coord	min;
	t_coord	max;
	t_coord	res;
	int		t;
	int		best;

	t = f->t.shape->max.row - f->t.shape->min.row + 1;
	min.row = f->b.min.row > t ? f->b.min.row - t : 0;
	max.row = f->b.max.row;
	t = f->t.shape->max.col - f->t.shape->min.col + 1;
	min.col = f->b.min.col > t ? f->b.min.col - t : 0;
	max.col = f->b.max.col;
	best = -1;
	while (min.row <= max.row)
	{
		t = min.col - 1;
		while (++t <= max.col)
		{
			set_coord(&res, min.row, t);
			try_place(f, res, &best);
		}
		min.row++;
	}
	return (best);
}

void		place_it(t_filler *f)
{
	ft_printf("%d %d\n", f->t.shape->best_place.row + f->t.corner.row,
		f->t.shape->best_place.col + f->t.corner.col);
}
