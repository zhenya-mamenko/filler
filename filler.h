/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 01:00:01 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/08 19:48:51 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# include "get_next_line/libft/libft.h"
# include <fcntl.h>

typedef struct	s_player
{
	int			id;
	char		c;
}				t_player;

typedef struct	s_cell
{
	char		v;
	int			weight;
}				t_cell;

typedef	struct	s_coord
{
	int			row;
	int			col;
}				t_coord;

typedef struct	s_board
{
	int			rows;
	int			cols;
	t_cell		**cells;
	t_coord		min;
	t_coord		max;
}				t_board;

typedef struct	s_shape
{
	t_coord		*p;
	int			cnt;
	t_coord		min;
	t_coord		max;
}				t_shape;

typedef struct	s_token
{
	t_shape		*shape;
	int			rows;
	int			cols;
	t_coord		corner;
}				t_token;

typedef struct s_filler
{
	t_player	p;
	t_board		b;
	t_token		t;
}				t_filler;

void			ft_free_array(int type, int count, void **a);
void			error(char *message);
int				ft_sqrt(int n);
void			set_coord(t_coord *c, int row, int col);
void			init_shape(t_shape *s, int rows, int cols);
void			compose_shape(t_token *t, int row, int col);
void			calc_shape_bounds(t_shape *s);
void			set_board_minmax(t_board *b, int row, int col, char c);
void			hitmap(t_filler *f);
t_coord			find_place(t_filler *f);

#endif