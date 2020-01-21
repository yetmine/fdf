#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/includes/libft.h"
# include "./minilibx/mlx.h"

# define WIN_WIDTH 2560
# define WIN_HEIGHT 1440
# define SCALE 20

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_window
{
	int			width;
	int			height;
	char		*name;
}				t_window;

typedef struct	s_map
{
	int			width;
	int			height;
	int			**data;
}				t_map;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_img		img;
	t_window	win;
}				t_fdf;

int				readFile(char *filename, t_fdf *fdf);
void			error(char *message);

#endif
