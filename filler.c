/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 00:04:58 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 12:00:56 by emamenko         ###   ########.fr       */
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
	if (s[1] != '2')
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

void	write_board(t_filler *f)
{
	int		i;
	int		j;

	i = 0;
	while (i < f->b.rows)
	{
		j = 0;
		while (j < f->b.cols)
		{
			ft_printf("% 3d", f->b.cells[i][j].weight);
			j++;
		}
		ft_printf("\n");
		i++;
	}
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
			ft_printf("0 0\n");
		else
			place_it(&f);
	}
}
