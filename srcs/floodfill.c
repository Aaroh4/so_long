/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:53:55 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:13:38 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


void	ft_true_false(t_img	*map_i)
{
	int	i;
	int	j;

	i = 0;
	map_i->true_false = malloc((map_i->count + 1) * (sizeof(char *)));
	if (map_i->true_false == NULL)
		ft_error_free(map_i, 1);
	while (i <= map_i->count)
	{
		map_i->true_false[i] = malloc((map_i->lenght + 1) * (sizeof(char *)));
		if (map_i->true_false[i] == NULL)
			ft_error_free(map_i, 1);
		j = 0;
		while (j <= map_i->lenght)
		{
			map_i->true_false[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	ft_floodfill(t_img *map_i, int y, int x)
{
	map_i->true_false[y][x] = '1';
	if ((map_i->map[y][x + 1] == '0' && map_i->true_false[y][x + 1] != '1')
	|| (map_i->map[y][x + 1] == 'C' && map_i->true_false[y][x + 1] != '1')
	|| (map_i->map[y][x + 1] == 'E' && map_i->true_false[y][x + 1] != '1'))
		ft_floodfill(map_i, y, x + 1);
	if ((map_i->map[y][x - 1] == '0' && map_i->true_false[y][x - 1] != '1')
	|| (map_i->map[y][x - 1] == 'C' && map_i->true_false[y][x - 1] != '1')
	|| (map_i->map[y][x - 1] == 'E' && map_i->true_false[y][x - 1] != '1'))
		ft_floodfill(map_i, y, x - 1);
	if ((map_i->map[y + 1][x] == '0' && map_i->true_false[y + 1][x] != '1')
	|| (map_i->map[y + 1][x] == 'C' && map_i->true_false[y + 1][x] != '1')
	|| (map_i->map[y + 1][x] == 'E' && map_i->true_false[y + 1][x] != '1'))
		ft_floodfill(map_i, y + 1, x);
	if ((map_i->map[y - 1][x] == '0' && map_i->true_false[y - 1][x] != '1')
	|| (map_i->map[y - 1][x] == 'C' && map_i->true_false[y - 1][x] != '1')
	|| (map_i->map[y - 1][x] == 'E' && map_i->true_false[y - 1][x] != '1'))
		ft_floodfill(map_i, y - 1, x);
}

void	ft_check_flood(t_img *map_i)
{
	int	i;
	int	j;
	int	collectible;
	int	exit;

	i = 0;
	exit = 0;
	collectible = 0;
	while (i < map_i->count)
	{
		j = 0;
		while (j < map_i->lenght)
		{
			if (map_i->map[i][j] == 'C' && map_i->true_false[i][j] == '1')
				collectible++;
			else if (map_i->map[i][j] == 'E' && map_i->true_false[i][j] == '1')
				exit++;
			j++;
		}
		i++;
	}
	if (collectible != map_i->collectible_c || exit != 1)
		ft_error_free(map_i, 3);
}
