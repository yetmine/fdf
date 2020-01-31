/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:37:33 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/31 13:33:03 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	is_perspective(int key, t_fdf *fdf)
{
	if (key == 35)
	{
		if (fdf->events.perspective == 0)
			fdf->events.perspective = 1;
		else
			fdf->events.perspective = 0;
	}
}

static void	change_view(int key, t_fdf *fdf)
{
	if (key == 17)
	{
		fdf->angle_x = 0.0;
		fdf->angle_y = 0.0;
		fdf->angle_z = 0.0;
	}
	if (key == 3)
	{
		fdf->angle_x = -1.57;
		fdf->angle_y = 0.0;
		fdf->angle_z = 0.0;
	}
	if (key == 15)
	{
		fdf->angle_x = -1.57;
		fdf->angle_y = 0.0;
		fdf->angle_z = 1.57;
	}
}

static void	open_help(int key, t_fdf *fdf)
{
	if (key == 4)
	{
		if (fdf->events.help == 0)
			fdf->events.help = 1;
		else
			fdf->events.help = 0;
	}
}

static void	is_scale_rotation(int key, t_fdf *fdf)
{
	if (key == 24)
		fdf->scale += fdf->scale_mult;
	if (key == 27 && fdf->scale > fdf->scale_mult)
		fdf->scale -= fdf->scale_mult;
	if (key == 125)
		fdf->angle_x += 0.05;
	if (key == 126)
		fdf->angle_x -= 0.05;
	if (key == 124)
		fdf->angle_z += 0.05;
	if (key == 123)
		fdf->angle_z -= 0.05;
}

int			key_press(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	if (key == 53)
		close_window(param);
	if (key == 29)
		set_defaults(fdf);
	change_view(key, fdf);
	is_perspective(key, fdf);
	is_scale_rotation(key, fdf);
	open_help(key, fdf);
	redraw(fdf);
	return (0);
}
