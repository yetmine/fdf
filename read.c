/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:11:56 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/21 15:16:08 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*parseData(int fd, t_fdf *fdf)
{
	int		i;
	int		j;
	char	*line;
	char	**split;

	i = 0;
	if ((fdf->map.data = (int**)malloc(sizeof(int*) * fdf->map.height)) == NULL)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		j = -1;
		if ((fdf->map.data[i] = (int*)malloc(sizeof(int) * fdf->map.width)) == NULL)
			return (NULL);
		split = ft_strsplit(line, ' ');
		while (split[++j])
		{
			fdf->map.data[i][j] = ft_atoi(split[j]);
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
	char	*line;
	char	**split;

	i = -1;
	fdf->map.width = 0;
	fdf->map.height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		fdf->map.height++;
		if (fdf->map.width == 0)
		{
			split = ft_strsplit(line, ' ');
			while (split[++i])
			{
				fdf->map.width++;
				ft_strdel(&split[i]);
			}
			free(split);
		}
		ft_strdel(&line);
	}
	return (fdf);
}

int				readFile(char *filename, t_fdf *fdf)
{
	int		fd;

	if ((fdf = (t_fdf*)malloc(sizeof(t_fdf))) == NULL)
		return (0);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (0);
	if ((fdf = getDimensions(fd, fdf)) == NULL)
		return (0);
	close(fd);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (0);
	if ((fdf = parseData(fd, fdf)) == NULL)
		return (0);
	close(fd);
	return (1);
}
