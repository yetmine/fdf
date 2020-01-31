/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:50:04 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 16:31:30 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_pixel(t_fdf *fdf, int x, int y, int c)
{
	if ((y >= WIN_HEIGHT) || (x * 4 > fdf->img.size_l) || y < 0 ||
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

static void	draw_line(t_fdf *fdf, t_line line)
{
	t_xy	dlt;
	int		i;
	float	d;

	if (line.out)
		return ;
	dlt.x = line.x1 - line.x0;
	dlt.y = line.y1 - line.y0;
	i = -1;
	if (abs(dlt.x) >= abs(dlt.y))
		while (++i < abs(dlt.x))
		{
			d = (float)i / dlt.x;
			draw_pixel(fdf, line.x0 + copysign(i, dlt.x), line.y0 +
			copysign(round(d * dlt.y), dlt.y), get_color(fdf, line, dlt.x, i));
		}
	else
		while (++i < abs(dlt.y))
		{
			d = (float)i / dlt.y;
			draw_pixel(fdf, line.x0 + copysign(round(d * dlt.x), dlt.x),
			line.y0 + copysign(i, dlt.y), get_color(fdf, line, dlt.y, i));
		}
}

static void	draw_image(t_fdf *fdf)
{
	fdf->current.y = 0;
	while (fdf->current.y < fdf->map.height)
	{
		fdf->current.x = 0;
		while (fdf->current.x < fdf->map.width)
		{
			if (fdf->current.x < fdf->map.width - 1)
				draw_line(fdf, transform(fdf, 1, 0));
			if (fdf->current.y < fdf->map.height - 1)
				draw_line(fdf, transform(fdf, 0, 1));
			fdf->current.x++;
		}
		fdf->current.y++;
	}
}

static void	put_background(t_fdf *fdf)
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
	put_background(fdf);
	if (fdf->events.help == 1)
		help_menu(fdf);
	else
	{
		draw_image(fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			fdf->img.img_ptr, 0, 0);
		help_text(fdf);
	}
}
