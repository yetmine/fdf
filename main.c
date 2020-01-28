/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:58 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/27 17:18:45 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void putBackground(t_fdf *fdf)
{
	int	x;
	int y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			fdf->img.data[y * WIN_WIDTH + x] = B_COLOR;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}

static void createImage(t_fdf *fdf)
{
	fdf->img.bpp = 32;
	fdf->img.size_l = WIN_WIDTH * 4;
	fdf->img.endian = 0;
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_WIDTH);
	fdf->img.data = (int*)mlx_get_data_addr(fdf->img.img_ptr, &(fdf->img.bpp),
	&(fdf->img.bpp), &(fdf->img.endian));
}

static void createWindow(t_fdf *fdf, char *name)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, name);
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
	redraw(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, &keyPress, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
