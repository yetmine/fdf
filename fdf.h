#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/includes/libft.h"
# include "./minilibx/mlx.h"

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define DEF_SCALE 	30
# define B_COLOR 	0x2a2a2a
# define DEF_BS_C	0xff0043 	// altitude min color;
# define DEF_TOP_C	0x00aeff	// altitude max color;
# define DEF_TXT_C	0xe0e0e0	// text color;
# define DEF_TXT_2	0x191919	// text inverse color  (light background)
# define FOCAL		2000

# define DEF_AX		-1.0		// basic angle x, y, z;
# define DEF_AY		0.0
# define DEF_AZ		0.75

# define DEF_SHX	0			// basic shift;
# define DEF_SHY	0

/****
 * Shortcats
 ***/
# define MAP		(fdf->map.data)
# define MAP_ADJ	(fdf->map.data_adj)
# define MAP_CONV	(fdf->map.data_conv)
# define X			(fdf->current.x)
# define Y			(fdf->current.y)
# define AX			(fdf->angleX)
# define AY			(fdf->angleY)
# define AZ			(fdf->angleZ)
# define SHX		(fdf->shift.x)
# define SHY		(fdf->shift.y)

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	double		z0;
	double		z1;
	int			c0;
	int			c1;
	int			out;

}				t_line;

typedef struct	s_img
{
	void		*img_ptr;
	char		*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_window
{
	int			width;
	int			height;
}				t_window;

typedef struct	s_rgb_kb
{
	float		a;
	float		r;
	float		g;
	float		b;

}				t_rgb_kb;

typedef struct s_z_peak
{
	int				value;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_z_peak;

typedef struct	s_map
{
	int			width;
	int			height;
	int			**data;
	double		**data_adj;
	double		**data_conv;
	t_z_peak	z_min;
	t_z_peak	z_max;
}				t_map;

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

typedef struct	s_events
{
	char			mouse_3_press;	// bool for scroll pressed;
	t_xy			mouse_xy;		// storing base coordinates of mouse press;
	char			mouse_1_press;	// bool for L click pressed;
	char			perspective;	// bool for perspective;
	char			help;			// bool for view help;
	int				scale_mult;		// scale multiplyer for scroll;
}				t_events;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	double		angleX;
	double		angleY;
	double		angleZ;
	int			scale;
	t_rgb_kb	coeff_k;
	t_rgb_kb	coeff_b;
	t_xy		current;
	t_map		map;
	t_img		img;
	t_window	win;
	t_events	events;
	t_xy		shift;
}				t_fdf;

t_fdf			*readFile(char *file);
void			error(char *message);
void			redraw(t_fdf *fdf);
int				keyPress(int key, void *param);
void			drawImage(t_fdf *fdf);
t_line			transform(t_fdf *fdf, int dx, int dy);
int				ft_min(t_map map);
int				ft_max(t_map map);
int				mouse_release(int key, int x, int y, void *param);
int 			mouse_press(int key, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);

#endif
