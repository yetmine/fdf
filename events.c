/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:37:33 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 11:17:41 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	closeWindow(t_fdf *fdf)
{
	int i;

	i = -1;
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free(fdf->img.img_ptr);
	free(fdf->img.data);
	while (++i < fdf->map.height)
	{
		free(MAP[i]);
		free(MAP_ADJ[i]);
		free(MAP_CONV[i]);
	}
	free(MAP);
	free(MAP_ADJ);
	free(MAP_CONV);
	exit(0);
	return (0);
}

int		keyPress(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	//	close programm if ESC
	if (key == 53)
		closeWindow(fdf);
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

int			mouseMove(int x, int y, void *param)
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

int 		mousePress(int key, int x, int y, void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf*)param;
//	scale
	if (key == 5)
			fdf->scale += fdf->scale_mult;
	if (key == 4 && fdf->scale > fdf->scale_mult)
			fdf->scale -= fdf->scale_mult;

//	shift
	if (key == 3)
	{
		fdf->events.mouse_3_press = 1;
		fdf->events.mouse_xy.x = x;
		fdf->events.mouse_xy.y = y;
		mouseMove(x, y, param);
	}

//	rotate
	if (key == 1)
	{
		fdf->events.mouse_1_press = 1;
		fdf->events.mouse_xy.x = x;
		fdf->events.mouse_xy.y = y;
		mouseMove(x, y, param);
	}
	redraw(fdf);
	return (0);
}

int			mouseRelease(int key, int x, int y, void *param)
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
