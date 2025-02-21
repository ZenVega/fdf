/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:10:24 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/20 18:17:45 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Canvas and dimentions
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define PADDING 0.1			//in %

//Colors
#define C_ZERO 0xFF00C0F9	//NEON_BLUE
#define C_HIGH 0xFF39FF14	//NEON_GREEN
#define C_LOW 0xFFFF14AF	//PINK

//CONFIGS
#define PROJ_MAX 1			//number of projections
#define ROT_TIMER 2
#define TRANS_STEP 10
#define INIT_X_ANG 90.314159
#define INIT_Y_ANG -0.628319
#define INIT_Z_ANG -1.884956

//KEYS
#define KEY_SB_OPEN 91
#define KEY_SB_CLOSE 93
#define KEY_SEMIC 59
#define KEY_COMMA 39
#define KEY_DOT 46
#define KEY_SLASH 47
#define KEY_MINUS 45
#define KEY_EQUAL 61
#define KEY_C 99
#define KEY_N 110
#define KEY_P 112
#define KEY_Q 113
#define KEY_R 114
#define KEY_I 111
#define KEY_O 105
#define KEY_X 120
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_SHIFT 65505
#define KEY_BACKSPACE 65288
#define KEY_ARR_UP 65362
#define KEY_ARR_LEFT 65361
#define KEY_ARR_DOWN 65364
#define KEY_ARR_RIGHT 65363

//MENUE
#define LINE_HEIGHT 16
#define TEXT_COL 0xFFFFFFFF
#define MENU_LEN 23		//items in menu
#define M_Y_OFF 80		//Y-Offset
#define M_X_OFF 30		//X-Offset
#define M_COL 120		//Column Width

typedef struct s_menu {
	char	*keys[MENU_LEN];
	char	*vals[MENU_LEN];
}	t_menu;

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

typedef struct s_vector {
	double	delta_x;
	double	delta_y;
	double	delta_z;
	double	pixel_x;
	double	pixel_y;
	double	slope;
	int		pixels;
}	t_vector;

typedef struct s_point {
	int				x;
	int				y;
	int				z;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	float			proj_x;
	float			proj_y;
	unsigned int	color;
	unsigned int	color_height;
}	t_point;

typedef struct s_map {
	int		width;
	int		depth;
	int		highest_z;
	int		lowest_z;
	t_point	center;
	t_point	**matrix;
}	t_map;

typedef struct s_ang {
	double	ang_x;
	double	ang_y;
	double	ang_z;
	double	sin_x;
	double	cos_x;
	double	sin_y;
	double	cos_y;
	double	sin_z;
	double	cos_z;
}	t_ang;

typedef struct s_p {
	void		*mlx;
	void		*win;
	t_map		*map;
	t_img		img;
	t_menu		menu;
	int			width;
	int			height;
	int			mouse_x;
	int			mouse_y;
	int			noise;
	int			syscol;
	int			projection;
	int			shifted;
	float		zoom;
	t_ang		angles;
	int			x_rot;
	int			y_rot;
	int			z_rot;
	int			rot_timer;
	int			rot_speed;
	double		scale_factor;
	double		center_x;
	double		center_y;
}	t_p;
