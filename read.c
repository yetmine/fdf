/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:11:56 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/29 17:55:00 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			setLinearCoefficients(t_fdf *fdf)
{
	fdf->map.z_max.value = ft_max(fdf->map);
	fdf->map.z_min.value = ft_min(fdf->map);
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

static t_fdf	*parseData(int fd, t_fdf *fdf)
{
	int		i;
	int		j;
	int		n;
	char	*line;
	char	**split;

	i = 0;
	if ((MAP = (int**)malloc(sizeof(int*) * fdf->map.height)) == NULL)
		return (NULL);
	if ((MAP_ADJ = (double**)malloc(sizeof(double*) * fdf->map.height)) == NULL)
		return (NULL);
	if ((MAP_CONV = (double**)malloc(sizeof(double*) * fdf->map.height)) == NULL)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		j = -1;
		if ((MAP[i] = (int*)malloc(sizeof(int) * fdf->map.width)) == NULL)
			return (NULL);
		if ((MAP_ADJ[i] = (double*)malloc(sizeof(double) * fdf->map.width)) == NULL)
			return (NULL);
		if ((MAP_CONV[i] = (double*)malloc(sizeof(double) * fdf->map.width)) == NULL)
			return (NULL);
		split = ft_strsplit(line, ' ');
		while (split[++j])
		{
			n = ft_atoi(split[j]);
			MAP[i][j] = n;
			MAP_ADJ[i][j] = (double)n;
			MAP_CONV[i][j] = MAP_ADJ[i][j];
			ft_strdel(&split[j]);
		}
		i++;
		free(split);
	}
	return (fdf);
}

static t_fdf	*getDimensions(int fd, t_fdf *fdf)
{
	int		i;
	int		width;
	char	*line;
	char	**split;

	fdf->map.height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = -1;
		width = 0;
		fdf->map.height++;
		split = ft_strsplit(line, ' ');
		while (split[++i])
		{
			width++;
			ft_strdel(&split[i]);
		}
		free(split);
		ft_strdel(&line);
		if (fdf->map.height == 1)
			fdf->map.width = width;
		else if (fdf->map.width != width)
			return (NULL);
	}
	return (fdf);
}

t_fdf			*readFile(char *file)
{
	int		fd;
	t_fdf	*fdf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if ((fdf = (t_fdf*)malloc(sizeof(t_fdf))) == NULL)
		return (NULL);
	if ((fdf = getDimensions(fd, fdf)) == NULL)
		return (NULL);
	close(fd);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if ((fdf = parseData(fd, fdf)) == NULL)
		return (NULL);
	close(fd);
	setLinearCoefficients(fdf);
	return (fdf);
}
