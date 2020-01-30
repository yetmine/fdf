/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:54:01 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/29 12:03:10 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_min(t_map map)
{
	int	i;
	int	j;
	int	min;

	i = -1;
	min = map.data[0][0];
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			if (map.data[i][j] < min)
				min = map.data[i][j];
		}
	}
	return (min);
}

int	ft_max(t_map map)
{
	int	i;
	int	j;
	int	max;

	i = -1;
	max = map.data[0][0];
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			if (map.data[i][j] > max)
				max = map.data[i][j];
		}
	}
	return (max);
}
