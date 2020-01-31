/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:54:43 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 16:32:31 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			close_window(void *param)
{
	int		i;
	t_fdf	*fdf;

	i = -1;
	fdf = (t_fdf*)param;
	mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	while (++i < fdf->map.height)
	{
		free(MAP[i]);
		free(MAP_CONV[i]);
	}
	free(MAP);
	free(MAP_CONV);
	free(fdf);
	exit(0);
	return (0);
}

int			mouse_move(int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	if (fdf->events.mouse_3_press)
	{
		SHX = x - fdf->events.mouse_xy.x + SHX;
		SHY = y - fdf->events.mouse_xy.y + SHY;
	}
	if (fdf->events.mouse_1_press)
	{
		AZ = AZ + (float)(x - fdf->events.mouse_xy.x) / 150.0;
		AX = AX + (float)(y - fdf->events.mouse_xy.y) / 150.0;
	}
	fdf->events.mouse_xy.x = x;
	fdf->events.mouse_xy.y = y;
	redraw(fdf);
	return (0);
}

int			mouse_press(int key, int x, int y, void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf*)param;
	if (key == 5)
		fdf->scale += fdf->scale_mult;
	if (key == 4 && fdf->scale > fdf->scale_mult)
		fdf->scale -= fdf->scale_mult;
	if (key == 3)
	{
		fdf->events.mouse_3_press = 1;
		fdf->events.mouse_xy.x = x;
		fdf->events.mouse_xy.y = y;
		mouse_move(x, y, param);
	}
	if (key == 1)
	{
		fdf->events.mouse_1_press = 1;
		fdf->events.mouse_xy.x = x;
		fdf->events.mouse_xy.y = y;
		mouse_move(x, y, param);
	}
	if (key == 5 || key == 4)
		redraw(fdf);
	return (0);
}

int			mouse_release(int key, int x, int y, void *param)
{
	t_fdf	*fdf;

	x += 0;
	y += 0;
	fdf = (t_fdf*)param;
	if (key == 3)
		fdf->events.mouse_3_press = 0;
	if (key == 1)
		fdf->events.mouse_1_press = 0;
	redraw(fdf);
	return (0);
}
