/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:04:51 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:00:09 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


void	ft_create_floor(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->count)
	{
		j = 0;
		while (j < img->lenght)
		{
			mlx_image_to_window(img->mlx, img->floor, 50 * j, 50 * i);
			if (img->map[i][j] == 'E')
				mlx_image_to_window(img->mlx, img->exit, 50 * j, 50 * i);
			j++;
		}
		i++;
	}
}

void	ft_create_wall(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->count)
	{
		j = 0;
		while (j < img->lenght)
		{
			if (img->map[i][j] == '1')
				mlx_image_to_window(img->mlx, img->wall, 50 * j, 50 * i);
			else if (img->map[i][j] == 'P')
				mlx_image_to_window(img->mlx, img->player, 50 * j, 50 * i);
			else if (img->map[i][j] == 'C')
				mlx_image_to_window(img->mlx, img->collectible, 50 * j, 50 * i);
			j++;
		}
		i++;
	}
}

void	ft_init_textu(t_img *img)
{
	img->player_txt = mlx_load_png("tiles/player.png");
	if (img->player_txt == NULL)
		ft_error_mlx(img);
	img->wall_txt = mlx_load_png("tiles/wall.png");
	if (img->wall_txt == NULL)
		ft_error_mlx(img);
	img->floor_txt = mlx_load_png("tiles/floor.png");
	if (img->floor_txt == NULL)
		ft_error_mlx(img);
	img->collectible_txt = mlx_load_png("tiles/collectible.png");
	if (img->collectible_txt == NULL)
		ft_error_mlx(img);
	img->exit_txt = mlx_load_png("tiles/exit.png");
	if (img->exit_txt == NULL)
		ft_error_mlx(img);
}

void	ft_init_img(mlx_t *mlx, t_img *img)
{
	img->player = mlx_texture_to_image(mlx, img->player_txt);
	if (img->player == NULL)
		ft_error_mlx(img);
	mlx_delete_texture(img->player_txt);
	img->wall = mlx_texture_to_image(mlx, img->wall_txt);
	if (img->wall == NULL)
		ft_error_mlx(img);
	mlx_delete_texture(img->wall_txt);
	img->floor = mlx_texture_to_image(mlx, img->floor_txt);
	if (img->floor == NULL)
		ft_error_mlx(img);
	mlx_delete_texture(img->floor_txt);
	img->collectible = mlx_texture_to_image(mlx, img->collectible_txt);
	if (img->collectible == NULL)
		ft_error_mlx(img);
	mlx_delete_texture(img->collectible_txt);
	img->exit = mlx_texture_to_image(mlx, img->exit_txt);
	if (img->exit == NULL)
		ft_error_mlx(img);
	mlx_delete_texture(img->exit_txt);
}

int	ft_check_ber(char *name, int i)
{
	if (name[i - 1] != 'r')
		return (0);
	if (name[i - 2] != 'e')
		return (0);
	if (name[i - 3] != 'b')
		return (0);
	if (name[i - 4] != '.')
		return (0);
	return (1);
}
