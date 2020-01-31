/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:11:56 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/31 13:45:23 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*parse_data(int fd, t_fdf *fdf)
{
	int		i;
	int		j;
	char	*line;
	char	**split;

	i = 0;
	fdf->map.data = (int**)malloc(sizeof(int*) * fdf->map.height);
	fdf->map.data_conv = (double**)malloc(sizeof(double*) * fdf->map.height);
	while (get_next_line(fd, &line))
	{
		j = -1;
		fdf->map.data[i] = (int*)malloc(sizeof(int) * fdf->map.width);
		fdf->map.data_conv[i] = (double*)malloc(sizeof(double)
			* fdf->map.width);
		split = ft_strsplit(line, ' ');
		while (split[++j])
		{
			fdf->map.data[i][j] = ft_atoi(split[j]);
			fdf->map.data_conv[i][j] = (double)fdf->map.data[i][j];
			ft_strdel(&split[j]);
		}
		i++;
		free(split);
	}
	return (fdf);
}

static t_fdf	*get_dimensions(int fd, t_fdf *fdf)
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

t_fdf			*read_file(char *file)
{
	int		fd;
	t_fdf	*fdf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if ((fdf = (t_fdf*)malloc(sizeof(t_fdf))) == NULL)
		return (NULL);
	if ((fdf = get_dimensions(fd, fdf)) == NULL)
		return (NULL);
	close(fd);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if ((fdf = parse_data(fd, fdf)) == NULL)
		return (NULL);
	close(fd);
	return (fdf);
}
