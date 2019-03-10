/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 00:04:58 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/09 17:46:35 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_player_data(t_player *p, const int fd)
{
	char	*s;
	char	*line;

	if (get_next_line(fd, &line) <= 0)
		error("reading player data");
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

void	get_token(t_token *t, const int fd)
{
	char	*line;
	char	**s;
	int		i;
	int		j;

	if (get_next_line(fd, &line) <= 0)
		error("reading token props");
	s = ft_strsplit(line, ' ');
	ft_strdel(&line);
	t->rows = ft_atoi(s[1]);
	t->cols = ft_atoi(s[2]);
	ft_free_array(1, 0, (void **)s);
	if (t->shape != NULL)
	{
		if (t->shape->p != NULL)
			free(t->shape->p);
		free(t->shape);
	}
	t->shape = malloc(sizeof(t_shape));
	init_shape(t->shape, t->rows, t->cols);
	i = 0;
	while (i < t->rows && (get_next_line(fd, &line) > 0))
	{
		j = -1;
		while (++j < t->cols)
			if (line[j] == '*')
				compose_shape(t, i, j);
		ft_strdel(&line);
		i++;
	}
	calc_shape_bounds(t->shape);
}

int		main(void)
{
	t_filler	f;
	int			fd;
	char		*line;

	fd = 0;
	get_player_data(&(f.p), fd);
	f.b.rows = 0;
	f.t.shape = NULL;
	while (1 > 0)
	{
		if (init_board(&(f.b), fd, f.b.rows) == 0)
			break ;
		get_next_line(fd, &line);
		ft_strdel(&line);
		fill_board(&(f.b), &(f.p), fd);
		get_token(&(f.t), fd);
		hitmap(&f);
		if (find_place(&f) <= -100)
			ft_printf("-100 -100\n");
		else
			place_it(&f);
	}
}
