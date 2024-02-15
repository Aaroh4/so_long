/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:41 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/15 17:25:21 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_error_mlx(t_img *map)
{
	ft_printf("%s\n", (mlx_strerror(mlx_errno)));
	ft_free_map(map);
	exit(1);
}

void	ft_error_str(char *str)
{
	free(str);
	write(1, "Error: Line count was 0\n", 24);
	exit(0);
}

void	ft_error_free(t_img *img, int i)
{
	ft_free_map(img);
	if (i == 1)
		write(1, "Error: Malloc failed\n", 21);
	else if (i == 2)
		write(1, "Error: Map isnt correct\n", 24);
	else if (i == 3)
	{
		write(1, "Error: Map doesnt have correct route\n", 37);
		ft_free_flood(img);
	}
	else if (i == 4)
		write(1, "Error: FD failed\n", 17);
	exit(0);
}

void	ft_free_map(t_img *img)
{
	int	i;

	i = img->count - 1;
	while (i >= 0)
	{
		free(img->map[i]);
		img->map[i] = NULL;
		i--;
	}
	free(img->map);
	img->map = NULL;
}

void	ft_free_flood(t_img *img)
{
	int	i;

	i = img->count;
	while (i >= 0)
	{
		free(img->true_false[i]);
		img->true_false[i] = NULL;
		i--;
	}
	free(img->true_false);
	img->true_false = NULL;
}
