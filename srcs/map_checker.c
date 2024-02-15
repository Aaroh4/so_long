/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:54:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:24:26 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_map_correct(char *str, t_img *struct_map, int line_count)
{
	int			i;
	static int	exit;
	static int	collectible;
	static int	player;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i++] == 'P')
		{
			struct_map->pos_x = i - 1;
			struct_map->pos_y = line_count;
			player++;
		}
		else if (str[i - 1] == 'C')
			collectible++;
		else if (str[i - 1] == 'E')
			exit++;
		else if (str[i - 1] != '1' && str[i - 1] != '0')
			return (-1);
	}
	struct_map->collectible_c = collectible;
	if (player == 1 && exit == 1 && collectible >= 1)
		return (1);
	return (0);
}

int	ft_wall_correct(char *str, int line, int line_count, int chars)
{
	int	i;

	i = 0;
	if (line == 0 || line == line_count - 1)
	{
		while (str[i] && str[i] != '\n')
		{
			if (str[i] != '1')
				return (0);
			i++;
		}
		if (i != chars && line != 0)
			return (0);
		return (i);
	}
	while (str[i] != '\n')
	{
		if ((str[i] != '1' && i == 0) 
			|| (str[i] != '1' && i == chars))
			return (0);
		i++;
	}
	if (i != chars)
		return (0);
	return (i);
}

void	ft_find_map(char *map_name, int line_count, t_img *s_map)
{
	int		i;
	char	**map;
	int		fd;
	int		correct;

	i = 0;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_error_free(s_map, 4);
	map = malloc((line_count + 1) * (sizeof(char *)));
	if (map == NULL)
		ft_error_free(s_map, 1);
	while (i != line_count)
	{
		map[i] = get_next_line(fd);
		correct = ft_map_correct(map[i], s_map, i);
		s_map->lenght = ft_wall_correct(map[i], i, line_count, s_map->lenght);
		if (s_map->lenght == 0 || correct == -1)
			ft_error_free(s_map, 2);
		i++;
	}
	close(fd);
	if (correct == 0)
		ft_error_free(s_map, 2);
	s_map->map = map;
}

void	ft_map_init(char *map_name, t_img *map)
{
	int		line_count;
	int		fd;
	char	*str;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_error_free(map, 4);
	line_count = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		free(str);
		str = get_next_line(fd);
		line_count++;
	}
	close(fd);
	if (line_count == 0)
		ft_error_str(str);
	ft_find_map(map_name, line_count, map);
	map->count = line_count;
	ft_true_false(map);
	ft_floodfill(map, map->pos_y, map->pos_x);
	ft_check_flood(map);
}
