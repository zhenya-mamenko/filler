/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:59:34 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/08 01:56:13 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	error(char *message)
{
	perror(message);
	exit(1);
}

void	ft_free_array(int type, int count, void **a)
{
	int		**a1;
	char	**a2;
	int		i;

	i = 0;
	if (type == 1)
		a2 = (char **)a;
	else if (type == 2)
		a1 = (int **)a;
	while ((count == 0 && type == 1 && *a2) || (count != 0 && i < count))
		if (type == 1)
		{
			if (*a2)
				free(*a2);
			*a2 = NULL;
			a2++;
		}
		else if (type == 2)
		{
			if (*a1)
				free(*a1);
			*a1 = NULL;
			a1++;
		}
}
