/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 00:04:58 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/08 10:21:03 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_player_data(t_player *p, const int fd)
{
	char	*s;
	char	*line;

	if (get_next_line(fd, &line) <= 0)
		error("reading player data.");
	s = ft_extract_word(line, ' ', 3);
	if (s[2] != '2')
	{
		p->id = 1;
		p->c = 'O';
	}
	else
	{
		p->id = 2;
		p->c = 'X';
	}
	ft_strdel(&s);
	ft_strdel(&line);
}

void	init_board(t_board *b, const int fd)
{
	char	*s;
	int		i;
	void	*p;
	char	*line;

	if (get_next_line(fd, &line) <= 0)
		error("reading board props.");
	s = ft_extract_word(line, ' ', 2);
	b->rows = ft_atoi(s);
	ft_strdel(&s);
	s = ft_extract_word(line, ' ', 3);
	b->cols = ft_atoi(s);
	p = malloc(sizeof(t_cell *) * (b->rows));
	b->cells = p;
	i = 0;
	while (i++ < b->rows)
	{
		*(b->cells) = malloc(sizeof(t_cell) * (b->cols));
		(b->cells)++;
	}
	b->cells = p;
	ft_strdel(&s);
	ft_strdel(&line);
}

void	fill_board(t_board *b, int r, t_player *p, const int fd)
{
	t_cell	*row;
	char	*s;
	int		i;
	char	*line;

	while (++r < b->rows)
	{
		if (get_next_line(fd, &line) <= 0)
			error("reading board data.");
		s = ft_extract_word(line, ' ', 2);
		i = -1;
		row = b->cells[r];
		while (++i < b->cols)
		{
			row[i].v = ft_toupper(s[i]);
			if (row[i].v == '.')
				row[i].weight = 0;
			else if (row[i].v == p->c)
				row[i].weight = 10000;
			else
				row[i].weight = -10000;
		}
		ft_strdel(&s);
		ft_strdel(&line);
	}
}

void	get_token(t_board *b, t_token *t, const int fd)
{
	char	*line;
	char	**s;
	int		i;
	int		j;
	int		ret;

	if (get_next_line(fd, &line) <= 0)
		error("reading token props.");
	s = ft_strsplit(line, ' ');
	t->rows = ft_atoi(s[1]);
	t->cols = ft_atoi(s[2]);
	ft_free_array(1, 0, (void **)s);
	t->shape = malloc(sizeof(t_shape));
	init_shape(t->shape, t->rows, t->cols);
	i = -1;
	while ((ret = get_next_line(fd, &line)) > 0 && ++i < t->rows)
	{
		j = -1;
		while (++j < t->cols)
			if (line[j] == '*')
				compose_shape(t, i, j);
		ft_strdel(&line);
	}
	calc_shape_bounds(t->shape);
}

int		main(void)
{
	t_filler	f;
	int			fd;
	int			r;
	char		*line;

	fd = open("/nfs/2018/e/emamenko/projects/filler/log.txt", O_RDONLY);
	get_player_data(&(f.p), fd);
	init_board(&(f.b), fd);
	get_next_line(fd, &line);
	r = -1;
	fill_board(&(f.b), r, &(f.p), fd);
	get_token(&(f.b), &(f.t), fd);
	close(fd);
}
