/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:37:33 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/29 16:50:24 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free(fdf->img.img_ptr);
	free(fdf->img.data);
	exit(0);
	return (0);
}

int		keyPress(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	//	close programm if ESC
	if (key == 53)
		close_window(fdf);
	//	top
	if (key == 17)
	{
		AX = 0.0;
		AY = 0.0;
		AZ = 0.0;
	}
//	front
	if (key == 3)
	{
		AX = -1.57;
		AY = 0.0;
		AZ = 0.0;
	}
//	right
	if (key == 15)
	{
		AX = -1.57;
		AY = 0.0;
		AZ = 1.57;
	}
	//	perspective
	if (key == 35 && fdf->events.perspective == 0)
			fdf->events.perspective = 1;
	else if (key == 35 && fdf->events.perspective == 1)
			fdf->events.perspective = 0;
	redraw(fdf);
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

int 		mouse_press(int key, int x, int y, void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf*)param;
//	scale
	if (key == 5)
			fdf->scale += fdf->events.scale_mult;
	if (key == 4 && fdf->scale > fdf->events.scale_mult)
			fdf->scale -= fdf->events.scale_mult;

//	shift
	if (key == 3)
	{
		fdf->events.mouse_3_press = 1;
		fdf->events.mouse_xy.x = x;
		fdf->events.mouse_xy.y = y;
		mouse_move(x, y, param);
	}

//	rotate
	if (key == 1)
	{
		fdf->events.mouse_1_press = 1;
		fdf->events.mouse_xy.x = x;
		fdf->events.mouse_xy.y = y;
		mouse_move(x, y, param);
	}
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
