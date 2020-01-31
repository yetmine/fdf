/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:12:30 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 16:23:48 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(t_fdf *fdf, t_line *line, int dx, int dy)
{
	int	temp0;
	int	temp1;

	temp0 = line->y0;
	temp1 = line->y1;
	line->y0 = (float)line->y0 * cos(AX) +
		(float)(MAP_CONV[Y][X]) * sin(AX);
	line->y1 = (float)line->y1 * cos(AX) +
		(float)(MAP_CONV[Y + dy][X + dx]) * sin(AX);
	MAP_CONV[Y][X] = (float)-temp0 * sin(AX) +
		(MAP_CONV[Y][X]) * cos(AX);
	MAP_CONV[Y + dy][X + dx] = (float)-temp1 * sin(AX) +
		(MAP_CONV[Y + dy][X + dx]) * cos(AX);
	line->z0 = MAP_CONV[Y][X];
	line->z1 = MAP_CONV[Y + dy][X + dx];
}

static void	rotate_y(t_fdf *fdf, t_line *line, int dx, int dy)
{
	int	temp0;
	int	temp1;

	temp0 = line->x0;
	temp1 = line->x1;
	line->x0 = (float)line->x0 * cos(AY) +
		(float)(MAP[Y][X] * fdf->scale) * sin(AY);
	line->x1 = (float)line->x1 * cos(AY) +
		(float)(MAP[Y + dy][X + dx] * fdf->scale) * sin(AY);
	MAP_CONV[Y][X] = -temp0 * sin(AY) +
		(float)(MAP[Y][X] * fdf->scale) * cos(AY);
	MAP_CONV[Y + dy][X + dx] = -temp1 * sin(AY) +
		(float)(MAP[Y + dy][X + dx] * fdf->scale) * cos(AY);
}

static void	rotate_z(t_fdf *fdf, t_line *line, int dx, int dy)
{
	float	cx;
	float	cy;

	cx = (float)X - (float)fdf->map.width / 2 + 0.5;
	cy = (float)Y - (float)fdf->map.height / 2 + 0.5;
	line->x0 = ((float)cx * cos(AZ) - (float)cy * sin(AZ)) *
		(float)fdf->scale;
	line->y0 = ((float)cx * sin(AZ) + (float)cy * cos(AZ)) *
		(float)fdf->scale;
	line->x1 = ((float)(cx + dx) * cos(AZ) -
		(float)(cy + dy) * sin(AZ)) * (float)fdf->scale;
	line->y1 = ((float)(cx + dx) * sin(AZ) +
		(float)(cy + dy) * cos(AZ)) * (float)fdf->scale;
	line->z0 = (float)MAP_CONV[Y][X];
	line->z1 = (float)MAP_CONV[Y + dy][X + dx];
}

static void	perspective(t_line *line)
{
	t_xy	old0;
	t_xy	old1;

	old0.x = line->x0;
	old0.y = line->y0;
	old1.x = line->x1;
	old1.y = line->y1;
	line->x0 = 3000 * line->x0 / (float)(3000 - line->z0);
	line->y0 = 3000 * line->y0 / (float)(3000 - line->z0);
	line->x1 = 3000 * line->x1 / (float)(3000 - line->z1);
	line->y1 = 3000 * line->y1 / (float)(3000 - line->z1);
	if ((old0.x > 0 && line->x0 < 0) || (old0.x < 0 && line->x0 > 0) ||
	(old0.y > 0 && line->y0 < 0) || (old0.y < 0 && line->y0 > 0) ||
	(old1.x > 0 && line->x1 < 0) || (old1.x < 0 && line->x1 > 0) ||
	(old1.y > 0 && line->y1 < 0) || (old1.y < 0 && line->y1 > 0))
	{
		line->x0 = 0;
		line->y0 = 0;
		line->x1 = 0;
		line->y1 = 0;
	}
}

t_line		transform(t_fdf *fdf, int dx, int dy)
{
	t_line line;

	line.out = 0;
	line.c0 = (int)MAP[Y][X];
	line.c1 = (int)MAP[Y + dy][X + dx];
	rotate_z(fdf, &line, dx, dy);
	rotate_y(fdf, &line, dx, dy);
	rotate_x(fdf, &line, dx, dy);
	if (fdf->events.perspective == 1)
		perspective(&line);
	line.x0 += WIN_WIDTH / 2 + SHX;
	line.x1 += WIN_WIDTH / 2 + SHX;
	line.y0 += WIN_HEIGHT / 2 + SHY;
	line.y1 += WIN_HEIGHT / 2 + SHY;
	if (((line.x0 > WIN_WIDTH || line.x0 < 0) ||
		(line.y0 > WIN_HEIGHT || line.y0 < 0)) &&
		((line.x1 > WIN_WIDTH || line.x1 < 0) ||
		(line.y1 > WIN_HEIGHT || line.y1 < 0)))
		line.out = 1;
	return (line);
}
