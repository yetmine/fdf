/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:12:30 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/31 13:57:21 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(t_fdf *fdf, t_line *line, int dx, int dy)
{
	int	temp0;
	int	temp1;

	temp0 = line->y0;
	temp1 = line->y1;
	line->y0 = (float)line->y0 * cos(fdf->angle_x) +
		(float)(fdf->map.data_conv[fdf->current.y][fdf->current.x])
		* sin(fdf->angle_x);
	line->y1 = (float)line->y1 * cos(fdf->angle_x) +
		(float)(fdf->map.data_conv[fdf->current.y + dy][fdf->current.x + dx])
		* sin(fdf->angle_x);
	fdf->map.data_conv[fdf->current.y][fdf->current.x] = (float)-temp0
		* sin(fdf->angle_x) + (fdf->map.data_conv[fdf->current.y]
		[fdf->current.x]) * cos(fdf->angle_x);
	fdf->map.data_conv[fdf->current.y + dy][fdf->current.x + dx] = (float)-temp1
		* sin(fdf->angle_x) + (fdf->map.data_conv[fdf->current.y + dy]
		[fdf->current.x + dx]) * cos(fdf->angle_x);
	line->z0 = fdf->map.data_conv[fdf->current.y][fdf->current.x];
	line->z1 = fdf->map.data_conv[fdf->current.y + dy][fdf->current.x + dx];
}

static void	rotate_y(t_fdf *fdf, t_line *line, int dx, int dy)
{
	int	temp0;
	int	temp1;

	temp0 = line->x0;
	temp1 = line->x1;
	line->x0 = (float)line->x0 * cos(fdf->angle_y) +
		(float)(fdf->map.data[fdf->current.y][fdf->current.x] * fdf->scale)
		* sin(fdf->angle_y);
	line->x1 = (float)line->x1 * cos(fdf->angle_y) +
		(float)(fdf->map.data[fdf->current.y + dy][fdf->current.x + dx]
		* fdf->scale) * sin(fdf->angle_y);
	fdf->map.data_conv[fdf->current.y][fdf->current.x] = -temp0
		* sin(fdf->angle_y) +
		(float)(fdf->map.data[fdf->current.y][fdf->current.x]
		* fdf->scale) * cos(fdf->angle_y);
	fdf->map.data_conv[fdf->current.y + dy][fdf->current.x + dx] = -temp1
		* sin(fdf->angle_y) +
		(float)(fdf->map.data[fdf->current.y + dy][fdf->current.x + dx]
		* fdf->scale) * cos(fdf->angle_y);
}

static void	rotate_z(t_fdf *fdf, t_line *line, int dx, int dy)
{
	float	cx;
	float	cy;

	cx = (float)fdf->current.x - (float)fdf->map.width / 2 + 0.5;
	cy = (float)fdf->current.y - (float)fdf->map.height / 2 + 0.5;
	line->x0 = ((float)cx * cos(fdf->angle_z) - (float)cy
		* sin(fdf->angle_z)) * (float)fdf->scale;
	line->y0 = ((float)cx * sin(fdf->angle_z) + (float)cy * cos(fdf->angle_z)) *
		(float)fdf->scale;
	line->x1 = ((float)(cx + dx) * cos(fdf->angle_z) -
		(float)(cy + dy) * sin(fdf->angle_z)) * (float)fdf->scale;
	line->y1 = ((float)(cx + dx) * sin(fdf->angle_z) +
		(float)(cy + dy) * cos(fdf->angle_z)) * (float)fdf->scale;
	line->z0 = (float)fdf->map.data_conv[fdf->current.y][fdf->current.x];
	line->z1 = (float)fdf->map.data_conv[fdf->current.y + dy]
		[fdf->current.x + dx];
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
	line.c0 = (int)fdf->map.data[fdf->current.y][fdf->current.x];
	line.c1 = (int)fdf->map.data[fdf->current.y + dy][fdf->current.x + dx];
	rotate_z(fdf, &line, dx, dy);
	rotate_y(fdf, &line, dx, dy);
	rotate_x(fdf, &line, dx, dy);
	if (fdf->events.perspective == 1)
		perspective(&line);
	line.x0 += WIN_WIDTH / 2 + fdf->shift.x;
	line.x1 += WIN_WIDTH / 2 + fdf->shift.x;
	line.y0 += WIN_HEIGHT / 2 + fdf->shift.y;
	line.y1 += WIN_HEIGHT / 2 + fdf->shift.y;
	if (((line.x0 > WIN_WIDTH || line.x0 < 0) ||
		(line.y0 > WIN_HEIGHT || line.y0 < 0)) &&
		((line.x1 > WIN_WIDTH || line.x1 < 0) ||
		(line.y1 > WIN_HEIGHT || line.y1 < 0)))
		line.out = 1;
	return (line);
}
