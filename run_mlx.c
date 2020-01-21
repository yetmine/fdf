/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:48:22 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/20 16:56:15 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	setWindowParams(t_fdf *fdf, char *name)
{
	fdf->win.name = ft_strjoin("FdF ", name);
	fdf->win.width = (fdf->map.height - 1) * SCALE * 4;
	if (fdf->win.width > WIN_WIDTH)
		fdf->win.width = WIN_WIDTH;
	else if (fdf->win.width < 700)
		fdf->win.width = 700;
	fdf->win.height = (fdf->win.width - 1) * SCALE * 4;
	if (fdf->win.height > (WIN_HEIGHT - 45))
		fdf->win.height = WIN_HEIGHT - 45;
	else if (fdf->win.height < 500)
		fdf->win.height = 500;
}
