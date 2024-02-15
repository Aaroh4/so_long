/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:16:42 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:12:18 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <fcntl.h>

typedef struct s_img
{
	int				count;
	int				lenght;
	int				pos_y;
	int				pos_x;
	int				collectible_c;
	mlx_t			*mlx;
	char			**map;
	char			**true_false;
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*player;
	mlx_image_t		*exit;
	mlx_image_t		*collectible;
	mlx_texture_t	*wall_txt;
	mlx_texture_t	*floor_txt;
	mlx_texture_t	*player_txt;
	mlx_texture_t	*exit_txt;
	mlx_texture_t	*collectible_txt;
}	t_img;

void	ft_key_hook(mlx_key_data_t keydata, void *param);
void	ft_map_init(char *map_name, t_img *map);
void	ft_find_map(char *map_name, int line_count, t_img *struct_map);
int		ft_wall_correct(char *str, int line, int line_count, int chars);
int		ft_map_correct(char *str, t_img *struct_map, int line_count);
void	ft_create_floor(t_img *img);
void	ft_create_wall(t_img *img);
void	ft_init_textu(t_img *img);
void	ft_init_img(mlx_t *mlx, t_img *img);
void	ft_error_free(t_img *img, int i);
void	ft_free_map(t_img *img);
void	ft_true_false(t_img	*map_info);
void	ft_floodfill(t_img *map_info, int y, int x);
void	ft_check_flood(t_img *map_info);
void	ft_free_flood(t_img *img);
void	ft_error_mlx(t_img *map);
void	ft_error_str(char *str);
int		ft_check_ber(char *name, int i);

#endif