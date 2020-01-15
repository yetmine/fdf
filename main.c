/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:58 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/14 15:54:25 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int keybord_process(int key, void *param)
// {
//     t_mlx *mlx;

//     mlx = (t_mlx*)param;
//     printf("%d\n", key);
//     if (key == 53)
//     {
//         free(mlx);
//         mlx_clear_window(mlx->mlx_ptr, mlx->mlx_window);
//         mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
//         exit(0);
//     }
//     return (0);
// }

/* int main()
{
    t_mlx *mlx;
    void *mlx_ptr;
    void *mlx_window;
    void *mlx_image;

    mlx_ptr = mlx_init();
    if (mlx_ptr != NULL)
    {
        mlx_window = mlx_new_window(mlx_ptr, 1000, 1000, "FdF");
        if (mlx_window != NULL)
        {
            //mlx_pixel_put(mlx_ptr, mlx_window, 500, 500, 0xffffff);
            if ((mlx = new_mlx(mlx_ptr, mlx_window)) != NULL)
            {
                mlx_key_hook(mlx_window, &keybord_process, (void*)mlx);
            }
            mlx_new_image(mlx_ptr, 500, 500);
            mlx_put_image_to_window(mlx_ptr, mlx_window, mlx_image, 40, 40);
            mlx_loop(mlx_ptr);
        }
    }
    return (0);
} */
#include "fdf.h"

#define MAX(a, b) (a > b ? a : b)

void setPixel(int x, int y, t_fdf *fdf)
{
	fdf->img.data[y * fdf->width + x] = 0xFFFFFF;
}

static void iso(int *x, int *y, int z)
{
	int temp;

	temp = *x;
	*x = (temp - *y) * cos(0.523599);
	*y = (temp + *y) * sin(0.523599) - z;
}

void drawLine(float x, float y, float x1, float y1, t_fdf *fdf) {
	int max;
	int z;
	int z1;
	int color;
	float x_step;
	float y_step;

	z = fdf->data[(int)y][(int)x];
	z1 = fdf->data[(int)y1][(int)x1];

	x *= fdf->zoom;
	y *= fdf->zoom;
	x1 *= fdf->zoom;
	y1 *= fdf->zoom;

	x_step = x1 - x;
	y_step = y1 - y;
	color = (z) ? 0xe80c0c : 0xFFFFFF;
	iso((int*)&x, (int*)&y, fdf->data[(int)y][(int)x]);
	iso((int*)&x1, (int*)&y1, fdf->data[(int)y1][(int)x1]);
	max = MAX(fabs(x_step), fabs(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x1 - x) || (int)(y1 - y))
	{
		//mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF);
		fdf->img.data[(int)y * WIN_WIDTH + (int)x] = color;
		x += x_step;
		y += y_step;
	}
}

int main(int argc, char **argv)
{
	int		x;
	int		y;
	t_fdf	*fdf;

	if (argc > 1)
	{
		if ((fdf = readFile(argv[1])) == NULL)
			exit(1);
		y = 0;
		fdf->mlx_ptr = mlx_init();
		fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
		fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, 1000, 1000);
		fdf->img.data = (int *)mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp, &fdf->img.size_l, &fdf->img.endian);
		while (y < fdf->height - 1)
		{
			x = 0;
			while (x < fdf->width - 1)
			{
				drawLine(x, y, x + 1, y, fdf);
				drawLine(x, y, x, y + 1, fdf);
				x++;
			}
			y++;
		}
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr,
			WIN_WIDTH / 2 - (fdf->width * fdf->zoom / 2), WIN_HEIGHT / 2 - (fdf->height * fdf->zoom / 2));
		mlx_loop(fdf->mlx_ptr);
	}
	return (0);
}
