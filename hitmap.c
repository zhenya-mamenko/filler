/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:04:48 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/09 15:54:56 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	lenweight(t_filler *f, t_coord c, t_coord p, t_coord b)
{
	int		s;
	int		i;
	int		j;
	int		k;

	if (f->b.cells[p.row][p.col].v == f->p.c)
		return (0);
	s = (c.row - p.row) * (c.row - p.row) + (c.col - p.col) * (c.col - p.col);
	j = ft_sqrt(s);
	s = (b.row - p.row) * (b.row - p.row) + (b.col - p.col) * (b.col - p.col);
	i = ft_sqrt(s);
	k = ft_sqrt(b.row * b.row + b.col * b.col) / 2 + 1;
	s = j * 2 + (k - i < 0 ? i - k : k - i) * 3;
	return (s);
}

static int	pt(t_filler *f, int row, int col)
{
	if (f->b.cells[row][col].v == '.')
		return (0);
	else if (f->b.cells[row][col].v == f->p.c)
		return (-1);
	else
		return (2);
}

static int	areaweight(t_filler *f, t_coord p)
{
	int		sum;

	if (f->b.cells[p.row][p.col].v == f->p.c)
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
	t_coord	b;
	int		tmp;

	tmp = f->t.shape->max.row - f->t.shape->min.row;
	min.row = f->b.min.row > tmp ? f->b.min.row - tmp : 0;
	max.row = f->b.max.row + tmp < f->b.rows ? f->b.max.row + tmp : f->b.rows - 1;
	tmp = f->t.shape->max.col - f->t.shape->min.col;
	min.col = f->b.min.col > tmp ? f->b.min.col - tmp : 0;
	max.col = f->b.max.col + tmp < f->b.cols ? f->b.max.col + tmp : f->b.cols - 1;
	set_coord(&cntr, (f->b.max.row - f->b.min.row) / 2,
		(f->b.max.col - f->b.min.col) / 2);
	while (min.row <= max.row)
	{
		tmp = min.col - 1;
		while (++tmp <= max.col)
		{
			set_coord(&b, f->b.rows, f->b.cols);
			f->b.cells[min.row][min.col].weight += lenweight(f, cntr, min, b);
			f->b.cells[min.row][min.col].weight += areaweight(f, min);
		}
		min.row++;
	}
}
