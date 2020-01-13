/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:19:58 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/13 15:08:55 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// typedef struct s_mlx
// {
//     void *mlx_ptr;
//     void *mlx_window;
// } t_mlx;


// t_mlx *new_mlx(void *mlx_ptr, void *mlx_window)
// {
//     t_mlx *mlx;

//     if ((mlx = (t_mlx*)malloc(sizeof(t_mlx))) == NULL)
//         return (NULL);
//     mlx->mlx_ptr = mlx_ptr;
//     mlx->mlx_window = mlx_window;
//     return (mlx);
// }

// #include <stdio.h>

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

void setPixel(int x, int y, t_fdf *fdf)
{
	fdf->img->data[x * 4 + 4 * fdf->width * y] = 0xFFFFFF;
}

void drawLine(int x0, int y0, int x1, int y1, t_fdf *fdf) {

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		setPixel(x0, y0, fdf);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

int main(int argc, char **argv)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	if (argc > 1)
	{
		if ((fdf = readFile(argv[1])) == NULL)
			exit(1);
		fdf->mlx_ptr = mlx_init();
		fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l,
			&fdf->img->endian);
		i = 0;
		while (i < fdf->height)
		{
			j = 0;
			while (j < fdf->width)
			{
				drawLine(fdf->data[i][j], fdf->data[i][j], fdf->data[i][j + 1], fdf->data[i][j + 1], fdf);
				drawLine(fdf->data[i][j], fdf->data[i][j], fdf->data[i + 1][j], fdf->data[i + 1][j], fdf);
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
		mlx_loop(fdf->mlx_ptr);
	}
	return (0);
}
