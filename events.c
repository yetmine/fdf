/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:54:43 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/31 13:46:42 by rabduras         ###   ########.fr       */
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
		free(fdf->map.data[i]);
		free(fdf->map.data_conv[i]);
	}
	free(fdf->map.data);
	free(fdf->map.data_conv);
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
		fdf->shift.x = x - fdf->events.mouse_xy.x + fdf->shift.x;
		fdf->shift.y = y - fdf->events.mouse_xy.y + fdf->shift.y;
	}
	if (fdf->events.mouse_1_press)
	{
		fdf->angle_z = fdf->angle_z + (float)(x - fdf->events.mouse_xy.x)
		/ 150.0;
		fdf->angle_x = fdf->angle_x + (float)(y - fdf->events.mouse_xy.y)
		/ 150.0;
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
