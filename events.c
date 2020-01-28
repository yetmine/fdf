/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:37:33 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/27 15:44:44 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free(fdf->img.img_ptr);
	free(fdf->img.data);
	exit(0);
	return (0);
}

int		keyPress(int key, void *param)
{
	//	close programm if ESC
	if (key == 53)
		close_window(param);
	return (0);
}
