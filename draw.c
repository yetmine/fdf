/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:50:04 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/29 17:16:47 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					color(t_fdf *fdf, t_line line, int delta, int i)
{
	int		c;
	float	r;
	float	g;
	float	b;

	if (line.c0 > line.c1)
	{
		r = (((float)line.c0 - fabsf(((float)(line.c1 - line.c0) /
			(float)delta) * i)) - fdf->coeff_b.r) / fdf->coeff_k.r;
		g = (((float)line.c0 - fabsf(((float)(line.c1 - line.c0) /
		(float)delta) * i)) - fdf->coeff_b.g) / fdf->coeff_k.g;
		b = (((float)line.c0 - fabsf(((float)(line.c1 - line.c0) /
			(float)delta) * i)) - fdf->coeff_b.b) / fdf->coeff_k.b;
	}
	else
	{
		r = (((float)line.c0 + fabsf(((float)(line.c1 - line.c0) /
		(float)delta) * i)) - fdf->coeff_b.r) / fdf->coeff_k.r;
		g = (((float)line.c0 + fabsf(((float)(line.c1 - line.c0) /
			(float)delta) * i)) - fdf->coeff_b.g) / fdf->coeff_k.g;
		b = (((float)line.c0 + fabsf(((float)(line.c1 - line.c0) /
		(float)delta) * i)) - fdf->coeff_b.b) / fdf->coeff_k.b;
	}
	c = ((int)r << 16) + ((int)g << 8) + b;

	//	if the map is flat;
	if (fdf->coeff_k.r == 0 && fdf->coeff_k.g == 0 && fdf->coeff_k.b == 0
		&& fdf->coeff_b.r == 0 && fdf->coeff_b.g == 0 && fdf->coeff_b.b == 0)
		c = DEF_BS_C;
	c += 0 << 24;
	return (c);
}

void drawPixel(t_fdf *fdf, int x, int y, int c)
{
	if ( (y >= WIN_HEIGHT) || (x * 4 > fdf->img.size_l) || y < 0 ||
			x * 4 < 0)
		return ;
	fdf->img.data[y * fdf->img.size_l + x * 4 + 3] =
		(unsigned char)((c & 0xFF000000) >> 24);
	fdf->img.data[y * fdf->img.size_l + x * 4 + 2] =
		(unsigned char)((c & 0xFF0000) >> 16);
	fdf->img.data[y * fdf->img.size_l + x * 4 + 1] =
		(unsigned char)((c & 0xFF00) >> 8);
	fdf->img.data[y * fdf->img.size_l + x * 4 + 0] =
		(unsigned char)(c & 0xFF);
}

void drawLine(t_fdf *fdf, t_line line)
{
	t_xy	delta;
	int		i;
	float	d;

	if (line.out)
		return;
	delta.x = line.x1 - line.x0;
	delta.y = line.y1 - line.y0;
	i = -1;
	if (abs(delta.x) >= abs(delta.y))
		while (++i < abs(delta.x))
		{
			d = (float)i / delta.x;
			drawPixel(fdf, line.x0 + copysign(i, delta.x), line.y0 +
				copysign(round(d * delta.y), delta.y), color(fdf, line, delta.x, i));
		}
	else
		while (++i < abs(delta.y))
		{
			d = (float)i / delta.y;
			drawPixel(fdf, line.x0 + copysign(round(d * delta.x), delta.x),
				line.y0 + copysign(i, delta.y), color(fdf, line, delta.y, i));
		}
}

void drawImage(t_fdf *fdf)
{
	fdf->current.y = 0;
	while (fdf->current.y < fdf->map.height)
	{
		fdf->current.x = 0;
		while (fdf->current.x < fdf->map.width)
		{
			if (fdf->current.x < fdf->map.width - 1)
				drawLine(fdf, transform(fdf, 1, 0));
			if (fdf->current.y < fdf->map.height - 1)
				drawLine(fdf, transform(fdf, 0, 1));
			fdf->current.x++;
		}
		fdf->current.y++;
	}
}
