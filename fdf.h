/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:51:26 by rabduras          #+#    #+#             */
/*   Updated: 2020/01/30 16:57:01 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define B_COLOR 	0x2A2A2A
# define DEF_BS_C	0xFF0043
# define DEF_TOP_C	0x00AEFF
# define DEF_AX		-1.0
# define DEF_AY		0.0
# define DEF_AZ		0.75
# define DEF_SHX	0
# define DEF_SHY	0
# define MAP		(fdf->map.data)
# define MAP_CONV	(fdf->map.data_conv)
# define X			(fdf->current.x)
# define Y			(fdf->current.y)
# define AX			(fdf->angle_x)
# define AY			(fdf->angle_y)
# define AZ			(fdf->angle_z)
# define SHX		(fdf->shift.x)
# define SHY		(fdf->shift.y)

typedef struct		s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	double			z0;
	double			z1;
	int				c0;
	int				c1;
	int				out;
}					t_line;

typedef struct		s_img
{
	void			*img_ptr;
	char			*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_rgb_kb
{
	float			r;
	float			g;
	float			b;
}					t_rgb_kb;

typedef struct		s_z_peak
{
	int				value;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_z_peak;

typedef struct		s_map
{
	int				width;
	int				height;
	int				**data;
	double			**data_conv;
	t_z_peak		z_min;
	t_z_peak		z_max;
}					t_map;

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_events
{
	t_xy			mouse_xy;
	char			help;
	char			mouse_1_press;
	char			mouse_3_press;
	char			perspective;
}					t_events;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				scale;
	int				scale_mult;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	t_xy			current;
	t_xy			shift;
	t_map			map;
	t_img			img;
	t_rgb_kb		coeff_k;
	t_rgb_kb		coeff_b;
	t_events		events;
}					t_fdf;

t_fdf				*read_file(char *file);
void				error(char *message);
void				redraw(t_fdf *fdf);
t_line				transform(t_fdf *fdf, int dx, int dy);
void				set_linear_coefficients(t_fdf *fdf);
int					get_color(t_fdf *fdf, t_line line, int delta, int i);
int					key_press(int key, void *param);
int					mouse_release(int key, int x, int y, void *param);
int					mouse_press(int key, int x, int y, void *param);
int					mouse_move(int x, int y, void *param);
int					close_window(void *param);
void				set_defaults(t_fdf *fdf);
int					ft_min(t_map map);
int					ft_max(t_map map);
void				help_text(t_fdf *fdf);
void				help_menu(t_fdf *fdf);

#endif
