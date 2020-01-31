/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:16:21 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/31 13:49:10 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void static	put_left_column(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 4,
		WIN_HEIGHT / 3 + 34 * (-4), 0xFFFFFF, "Hotkeys:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 4,
		WIN_HEIGHT / 3 + 34 * (-3), 0xFFFFFF, "Arrays  - Rotate");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 4,
		WIN_HEIGHT / 3 + 34 * (-2), 0xFFFFFF,
		"R  T  F - Right, Top, Front projection");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 4,
		WIN_HEIGHT / 3 + 34 * (-1), 0xFFFFFF,
		"P       - Perspective projection");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 4,
		WIN_HEIGHT / 3 + 34 * 0, 0xFFFFFF,
		"0       - reset zoom & rotation");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 4,
		WIN_HEIGHT / 3 + 34 * 1, 0xFFFFFF, "-  +    - zoom out, zoom in");
}

void static	put_right_column(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 2 + 160,
		WIN_HEIGHT / 3 + 34 * (-4), 0xFFFFFF, "Mouse keys:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 2 + 160,
		WIN_HEIGHT / 3 + 34 * (-3), 0xFFFFFF, "Hold left click to rotate");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 2 + 160,
		WIN_HEIGHT / 3 + 34 * (-2), 0xFFFFFF, "Hold scroll for panorama");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 2 + 160,
		WIN_HEIGHT / 3 + 34 * (-1), 0xFFFFFF,
		"Scroll for zoom in and zoom out");
}

void		help_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 2 - 100,
		WIN_HEIGHT / 3 + 34 * (-6), 0xFFFFFF, "FdF (Fils de Fer)");
	put_left_column(fdf);
	put_right_column(fdf);
}

void		help_text(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
		10, 10, 0xFFFFFF, "Press 'H' for help");
}
