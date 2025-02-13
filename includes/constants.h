/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:10:24 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/12 17:28:12 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Canvas and dimentions
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define PADDING 0.1			//in %

//Colors
#define C_ZERO 0xFFFFFFFF	//WHITE
#define C_HIGH 0xFF39FF14	//NEON_GREEN
#define C_LOW 0xFFFF14AF	//PINK

#define PROJ_MAX 2			//number of projections

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_proj {
	double	x_step;
	double	y_step;
	double	x_start;
	double	y_start;
	double	width;
	double	height;
	double	ratio;
}	t_proj;

typedef struct s_cursor {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*file;
	int		width;
	int		height;
}	t_cursor;

typedef struct s_vector {
	double	delta_x;
	double	delta_y;
	double	delta_z;
	double	pixel_x;
	double	pixel_y;
}	t_vector;

typedef struct s_point {
	int				x;
	int				y;
	int				z;
	float			proj_x;
	float			proj_y;
	unsigned int	color;
}	t_point;

typedef struct s_map {
	int		width;
	int		depth;
	int		highest_z;
	int		lowest_z;
	t_point	center;
	t_point	**matrix;
}	t_map;

typedef struct s_p {
	void		*mlx;
	void		*win;
	t_map		*map;
	t_img		img;
	t_cursor	cursor;
	int			width;
	int			height;
	int			mouse_x;
	int			mouse_y;
	int			noise;
	int			projection;
	int			update;
}	t_p;
