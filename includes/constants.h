/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:10:24 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/11 17:20:03 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

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
	int	ax;
	int	ay;
	int	bx;
	int	by;
}	t_vector;

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	float	proj_x;
	float	proj_y;
}	t_point;

typedef struct s_map {
	int		length;
	int		height;
	int		highest_z;
	int		lowest_z;
	t_point	**matrix;
}	t_map;

typedef struct s_p {
	void		*mlx;
	void		*win;
	t_map		*map;
	t_data		img;
	t_cursor	cursor;
	int			width;
	int			height;
	int			mouse_x;
	int			mouse_y;
}	t_p;
