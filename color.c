/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:01:13 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 12:07:44 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setLinearCoefficients(t_fdf *fdf)
{
	fdf->map.z_max.value = ftMax(fdf->map);
	fdf->map.z_min.value = ftMin(fdf->map);
	fdf->map.z_min.r = (DEF_BS_C >> 16);
	fdf->map.z_min.g = ((DEF_BS_C & 0xFF00) >> 8);
	fdf->map.z_min.b = (DEF_BS_C & 0xFF);
	fdf->map.z_max.r = (DEF_TOP_C >> 16);
	fdf->map.z_max.g = ((DEF_TOP_C & 0xFF00) >> 8);
	fdf->map.z_max.b = (DEF_TOP_C & 0xFF);
	fdf->coeff_k.r = ((float)fdf->map.z_min.value - (float)fdf->map.z_max.value /
		((float)fdf->map.z_min.r - (float)fdf->map.z_max.r));
	fdf->coeff_k.g = ((float)fdf->map.z_min.value - (float)fdf->map.z_max.value /
		((float)fdf->map.z_min.g - (float)fdf->map.z_max.g));
	fdf->coeff_k.b = ((float)fdf->map.z_min.value - (float)fdf->map.z_max.value /
		((float)fdf->map.z_min.b - (float)fdf->map.z_max.b));
	fdf->coeff_b.r = ((float)fdf->map.z_min.value -
		fdf->coeff_k.r * (float)fdf->map.z_min.r);
	fdf->coeff_b.g = (float)fdf->map.z_min.value -
		fdf->coeff_k.g * (float)fdf->map.z_min.g;
	fdf->coeff_b.b = (float)fdf->map.z_min.value -
		fdf->coeff_k.b * (float)fdf->map.z_min.b;
}

int		getColor(t_fdf *fdf, t_line line, int delta, int i)
{
	int		c;
	float	r;
	float	g;
	float	b;
	float	k;

	if (line.c0 > line.c1)
		k = ((float)line.c0 - fabsf(((float)(line.c1 - line.c0) /
			(float)delta) * i));
	else
		k = ((float)line.c0 + fabsf(((float)(line.c1 - line.c0) /
			(float)delta) * i));
	r = (k - fdf->coeff_b.r) / fdf->coeff_k.r;
	g = (k - fdf->coeff_b.g) / fdf->coeff_k.g;
	b = (k - fdf->coeff_b.b) / fdf->coeff_k.b;
	c = ((int)r << 16) + ((int)g << 8) + b;
	if (fdf->coeff_k.r == 0 && fdf->coeff_k.g == 0 && fdf->coeff_k.b == 0
		&& fdf->coeff_b.r == 0 && fdf->coeff_b.g == 0 && fdf->coeff_b.b == 0)
		c = DEF_BS_C;
	return (c);
}
