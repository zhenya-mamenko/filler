/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:04:48 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/12 01:18:00 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	pt(t_filler *f, int row, int col)
{
	if (f->b.cells[row][col].v == '.')
		return (2);
	else if (f->b.cells[row][col].v == f->p.c)
		return (-1);
	else
		return (2);
}

static int	eval_point(t_filler *f, t_coord c)
{
	int		i;
	int		j;
	int		sum;
	int		ac;
	int		ar;

	sum = 0;
	if (f->b.rows < 7 || f->b.cols < 7)
		return (pt(f, c.row, c.col));
	ar = f->b.rows / 20;
	ac = f->b.cols / 20;
	i = c.row - 1 - ac;
	while (i < c.row + 1 + ac)
	{
		j = c.col - 1 - ac;
		while (j < c.col + 1 + ac)
		{
			sum += pt(f, i, j);
			j++;
		}
		i++;
	}
	return (sum);
}

static int	lenweight(t_filler *f, t_coord c, t_coord p, int t)
{
	int		s;
	int		i;
	int		j;
	int		k;
	t_coord	b;

	p.col = t;
	set_coord(&b, f->b.rows / 2, f->b.cols / 2);
	if (f->b.cells[p.row][p.col].v != f->p.c &&
		f->b.cells[p.row][p.col].v != '.')
		return (0);
	s = (c.row - p.row) * (c.row - p.row) + (c.col - p.col) * (c.col - p.col);
	j = ft_sqrt(s);
	s = (b.row - p.row) * (b.row - p.row) + (b.col - p.col) * (b.col - p.col);
	i = ft_sqrt(s);
	k = ft_sqrt(b.row * b.row + b.col * b.col);
	j *= j < (k - 1) ? 3 : 1;
	k = (i > k) ? i - k : k - i;
	s = j + (eval_point(f, b) >= 0 ? k : i) * 2;
	return (s);
}

static int	areaweight(t_filler *f, t_coord p)
{
	int		sum;

	if (f->b.cells[p.row][p.col].v != f->p.c &&
		f->b.cells[p.row][p.col].v != '.')
		return (0);
	sum = 0;
	sum += (p.row > 0) ? pt(f, p.row - 1, p.col) : 2;
	sum += (p.row < f->b.rows - 1) ? pt(f, p.row + 1, p.col) : 2;
	sum += (p.col > 0) ? pt(f, p.row, p.col - 1) : 2;
	sum += (p.col < f->b.cols - 1) ? pt(f, p.row, p.col + 1) : 2;
	sum += (p.row != 0 && p.col != 0) ? pt(f, p.row - 1, p.col - 1) : 3;
	sum += (p.row != 0 && p.col != f->b.cols - 1) ?
		pt(f, p.row - 1, p.col + 1) : 3;
	sum += (p.row != f->b.rows - 1 && p.col != f->b.cols - 1) ?
		pt(f, p.row + 1, p.col + 1) : 3;
	sum += (p.row != f->b.rows - 1 && p.col != 0) ?
		pt(f, p.row + 1, p.col - 1) : 3;
	return (sum);
}

void		hitmap(t_filler *f)
{
	t_coord	min;
	t_coord	max;
	t_coord	cntr;
	int		t;

	t = f->t.shape->max.row - f->t.shape->min.row;
	min.row = f->b.min.row > t ? f->b.min.row - t : 0;
	max.row = f->b.max.row + t < f->b.rows - 1 ?
		f->b.max.row + t : f->b.rows - 1;
	t = f->t.shape->max.col - f->t.shape->min.col;
	min.col = f->b.min.col > t ? f->b.min.col - t : 0;
	max.col = f->b.max.col + t < f->b.cols - 1 ?
		f->b.max.col + t : f->b.cols - 1;
	set_coord(&cntr, (f->b.max.row - f->b.min.row) / 2 + f->b.min.row,
		(f->b.max.col - f->b.min.col) / 2 + f->b.min.col);
	while (min.row <= max.row)
	{
		t = min.col - 1;
		while (++t <= max.col)
			f->b.cells[min.row][t].weight += lenweight(f, cntr, min, t) +
				areaweight(f, min);
		min.row++;
	}
}
