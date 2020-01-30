/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:58 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 12:06:33 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH,
		WIN_HEIGHT, ft_strjoin("FdF ", name));
}

static void	setDefaults(t_fdf *fdf)
{
	AX = DEF_AX;
	AY = DEF_AY;
	AZ = DEF_AZ;
	SHX = DEF_SHX;
	SHY = DEF_SHY;
	fdf->scale = DEF_SCALE;
	fdf->scale_mult = 1;
}

int main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		error("usage: ./fdf [map.fdf]");
	if (!(fdf = readFile(argv[1])))
		error("Invalid map or file doesn't exist.");
	setLinearCoefficients(fdf);
	createWindow(fdf, argv[1]);
	createImage(fdf);
	setDefaults(fdf);
	redraw(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, &keyPress, (void *)fdf);
	mlx_hook(fdf->win_ptr, 4, 0, &mousePress, (void *)fdf);
	mlx_hook(fdf->win_ptr, 6, 0, &mouseMove, (void *)fdf);
	mlx_hook(fdf->win_ptr, 5, 0, &mouseRelease, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
