/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:50:04 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/27 17:55:11 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw(t_fdf *fdf, t_line *line)
{
	
}

void drawImage(t_fdf *fdf)
{
	int		x;
	int		y;
	t_line	line;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			line.x0 = x;
			line.x1 = x;
			line.y0 = y;
			line.y1 = y;
			if (x < fdf->map.width - 1)
			{
				line.x1  = line.x1 + 1;
				draw(fdf, &line);
			}
			if (y < fdf->map.height - 1)
			{
				line.y1  = line.y1 + 1;
				draw(fdf, &line);
			}
			x++;
		}
		y++;
	}
}
