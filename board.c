/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:14:17 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/09 16:42:59 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	set_board_minmax(t_board *b, int row, int col, char c)
{
	if (b->cells[row][col].v != c)
		return ;
	if (row > b->max.row)
		b->max.row = row;
	if (row < b->min.row)
		b->min.row = row;
	if (col > b->max.col)
		b->max.col = col;
	if (col < b->min.col)
		b->min.col = col;
}

int			init_board(t_board *b, const int fd, int flag)
{
	char	**s;
	int		i;
	void	*p;
	char	*line;
	int		res;

	if ((res = get_next_line(fd, &line)) < 0)
		error("reading board props");
	if (flag == 0)
	{
		s = ft_strsplit(line, ' ');
		b->rows = ft_atoi(s[1]);
		b->cols = ft_atoi(s[2]);
		ft_free_array(1, 0, (void **)s);
		p = malloc(sizeof(t_cell *) * (b->rows));
		b->cells = p;
		set_coord(&(b->min), 100000, 100000);
		set_coord(&(b->max), -100000, -100000);
		i = 0;
		while (i++ < b->rows)
		{
			*(b->cells) = malloc(sizeof(t_cell) * (b->cols));
			(b->cells)++;
		}
		b->cells = p;
	}
	ft_strdel(&line);
	return (res);
}

void		fill_board(t_board *b, t_player *p, const int fd)
{
	t_cell	*row;
	char	*s;
	int		i;
	char	*line;
	int		r;

	r = -1;
	while (++r < b->rows)
	{
		if (get_next_line(fd, &line) <= 0)
			error("reading board data");
		s = ft_extract_word(line, ' ', 2);
		i = -1;
		row = b->cells[r];
		while (++i < b->cols)
		{
			row[i].v = ft_toupper(s[i]);
			row[i].weight = 0;
			if (row[i].v != p->c && row[i].v != '.')
				row[i].weight = -1000000;
			set_board_minmax(b, r, i, p->c);
		}
		ft_strdel(&s);
		ft_strdel(&line);
	}
}
