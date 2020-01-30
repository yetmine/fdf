/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:58 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/29 16:21:18 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void putBackground(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->img.size_l * WIN_HEIGHT)
	{
		fdf->img.data[i + 3] = (unsigned char)0;
		fdf->img.data[i + 2] = (unsigned char)(B_COLOR >> 16);
		fdf->img.data[i + 1] = (unsigned char)((B_COLOR & 65280) >> 8);
		fdf->img.data[i] = (unsigned char)B_COLOR & 255;
		i += 4;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}

static void createImage(t_fdf *fdf)
{
	fdf->img.bpp = 32;
	fdf->img.size_l = WIN_WIDTH * 4;
	fdf->img.endian = 0;
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_WIDTH);
	fdf->img.data = mlx_get_data_addr(fdf->img.img_ptr, &(fdf->img.bpp),
	&(fdf->img.bpp), &(fdf->img.endian));
}

static void createWindow(t_fdf *fdf, char *name)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, name);
}

static void	setDefaults(t_fdf *fdf)
{
	fdf->angleX = DEF_AX;
	fdf->angleY = DEF_AY;
	fdf->angleZ = DEF_AZ;
	fdf->scale = DEF_SCALE;
	fdf->events.scale_mult = 1;
	SHX = DEF_SHX;
	SHY = DEF_SHY;
}

void redraw(t_fdf *fdf)
{
	putBackground(fdf);
	drawImage(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}

int main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		error("usage: ./fdf [map.fdf]");
	if (!(fdf = readFile(argv[1])))
		error("Invalid map or file doesn't exist.");
	createWindow(fdf, argv[1]);
	createImage(fdf);
	setDefaults(fdf);
	redraw(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, &keyPress, (void *)fdf);
	mlx_hook(fdf->win_ptr, 4, 0, &mouse_press, (void *)fdf);
	mlx_hook(fdf->win_ptr, 6, 0, &mouse_move, (void *)fdf);
	mlx_hook(fdf->win_ptr, 5, 0, &mouse_release, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
