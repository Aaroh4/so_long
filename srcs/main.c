/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:05:04 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:10:36 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_check_checkpoint(t_img *img)
{
	int	i;

	i = 0;
	if (img->map[img->pos_y][img->pos_x] == 'C')
	{
		while (img->collectible_c > 0)
		{
			if (img->collectible->instances[i].x / 50 == img->pos_x
				&& img->collectible->instances[i].y / 50 == img->pos_y)
			{
				if (img->collectible->instances[i].enabled != false)
					img->collectible_c -= 1;
				img->collectible->instances[i].enabled = false;
				break ;
			}
			i++;
		}
	}
	if (img->collectible_c == 0 
		&& img->map[img->pos_y][img->pos_x] == 'E')
		mlx_close_window(img->mlx);
}

int	ft_check_move(t_img *img, int move)
{
	static int	i;

	if (move == 1 && img->map[img->pos_y][img->pos_x - 1] != '1')
	{
		ft_printf("Move count: %d\n", ++i);
		img->pos_x -= 1;
	}
	else if (move == 2 && img->map[img->pos_y][img->pos_x + 1] != '1')
	{
		ft_printf("Move count: %d\n", ++i);
		img->pos_x += 1;
	}
	else if (move == 3 && img->map[img->pos_y - 1][img->pos_x] != '1')
	{
		ft_printf("Move count: %d\n", ++i);
		img->pos_y -= 1;
	}
	else if (move == 4 && img->map[img->pos_y + 1][img->pos_x] != '1')
	{
		ft_printf("Move count: %d\n", ++i);
		img->pos_y += 1;
	}
	else
		return (0);
	return (1);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_img	*img;

	img = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(img->mlx);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		if (ft_check_move(img, 1) == 1)
			img->player->instances[0].x -= 50;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		if (ft_check_move(img, 2) == 1)
			img->player->instances[0].x += 50;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		if (ft_check_move(img, 3) == 1)
			img->player->instances[0].y -= 50;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		if (ft_check_move(img, 4) == 1)
			img->player->instances[0].y += 50;
	ft_check_checkpoint(img);
}

void	ft_start_window(t_img *map_info)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	map_info->mlx = mlx_init(50 * map_info->lenght, 50 * map_info->count, "Game", false);
	mlx_get_monitor_size(0, &width, &height);
	if (width < map_info->lenght * 50 || height < map_info->count * 50)
	{
		write(1, "Error: map too big for the screen\n", 34);
		exit(0);
	}
	ft_init_textu(map_info);
	ft_init_img(map_info->mlx, map_info);
	ft_create_floor(map_info);
	ft_create_wall(map_info);
	mlx_key_hook(map_info->mlx, &ft_key_hook, map_info);
	mlx_loop(map_info->mlx);
	ft_free_map(map_info);
	ft_free_flood(map_info);
	mlx_terminate(map_info->mlx);
}

int	main(int argc, char **argv)
{
	char			*map_name;
	t_img			map_info;
	int				i;

	i = 0;

	if (argc != 2)
	{
		write(1, "Error: Wrong amount of arguments\n", 33);
		exit(0);
	}
	ft_memset(&map_info, 0, sizeof(map_info));
	map_name = argv[1];
	while (map_name[i] != '\0')
		i++;
	if (ft_check_ber(map_name, i) != 1)
	{
		write(1, "Error, Not .ber file", 20);
		exit(0);
	}
	ft_map_init(map_name, &map_info);
	ft_start_window(&map_info);
	return (0);
}
