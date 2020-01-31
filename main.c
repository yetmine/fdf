/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:58 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/31 13:37:22 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_image(t_fdf *fdf)
{
	fdf->img.bpp = 32;
	fdf->img.size_l = WIN_WIDTH * 4;
	fdf->img.endian = 0;
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_WIDTH);
	fdf->img.data = mlx_get_data_addr(fdf->img.img_ptr, &(fdf->img.bpp),
	&(fdf->img.bpp), &(fdf->img.endian));
}

static void	create_window(t_fdf *fdf, char *name)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH,
		WIN_HEIGHT, ft_strjoin("FdF ", name));
}

void		set_defaults(t_fdf *fdf)
{
	fdf->angle_x = AX;
	fdf->angle_y = AY;
	fdf->angle_z = AZ;
	fdf->shift.x = SHX;
	fdf->shift.y = SHY;
	fdf->scale = SCALE;
	fdf->scale_mult = 1;
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		error("usage: ./fdf [map.fdf]");
	if (!(fdf = read_file(argv[1])))
		error("Invalid map or file doesn't exist.");
	set_linear_coefficients(fdf);
	create_window(fdf, argv[1]);
	create_image(fdf);
	set_defaults(fdf);
	redraw(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, &key_press, (void *)fdf);
	mlx_hook(fdf->win_ptr, 4, 0, &mouse_press, (void *)fdf);
	mlx_hook(fdf->win_ptr, 6, 0, &mouse_move, (void *)fdf);
	mlx_hook(fdf->win_ptr, 5, 0, &mouse_release, (void *)fdf);
	mlx_hook(fdf->win_ptr, 17, 0, &close_window, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
