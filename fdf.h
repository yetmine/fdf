#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/includes/libft.h"
# include "./minilibx/mlx.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define SCALE 25
# define B_COLOR 0x2a2a2a

typedef struct	s_line
{
	float		x0;
	float		y0;
	float		x1;
	float		y1;
}				t_line;

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

t_fdf			*readFile(char *file);
void			error(char *message);
int				keyPress(int key, void *param);
void			drawImage(t_fdf *fdf);

#endif
