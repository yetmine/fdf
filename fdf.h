#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/includes/libft.h"
# include "./minilibx/mlx.h"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	int			**data;
	t_img		img;
}				t_fdf;

t_fdf			*readFile(char *filename);

#endif
