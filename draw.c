/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:50:04 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 12:08:59 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	drawPixel(t_fdf *fdf, int x, int y, int c)
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

static void	drawLine(t_fdf *fdf, t_line line)
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
				copysign(round(d * delta.y), delta.y), getColor(fdf, line, delta.x, i));
		}
	else
		while (++i < abs(delta.y))
		{
			d = (float)i / delta.y;
			drawPixel(fdf, line.x0 + copysign(round(d * delta.x), delta.x),
				line.y0 + copysign(i, delta.y), getColor(fdf, line, delta.y, i));
		}
}

static void	drawImage(t_fdf *fdf)
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

static void putBackground(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->img.size_l * WIN_HEIGHT)
	{
		fdf->img.data[i + 3] = 0;
		fdf->img.data[i + 2] = (unsigned char)((B_COLOR >> 16) & 255);
		fdf->img.data[i + 1] = (unsigned char)((B_COLOR >> 8) & 255);
		fdf->img.data[i] = (unsigned char)B_COLOR & 255;
		i += 4;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img.img_ptr, 0, 0);
}

void		redraw(t_fdf *fdf)
{
	putBackground(fdf);
	drawImage(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}
