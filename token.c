/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:00:05 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 12:00:43 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	prepare_token(t_token *t, const int fd)
{
	char	*line;
	char	**s;

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
}

void		get_token(t_token *t, const int fd)
{
	int		i;
	int		j;
	char	*line;

	prepare_token(t, fd);
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
