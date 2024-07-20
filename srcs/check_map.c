/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:33:35 by pbailly           #+#    #+#             */
/*   Updated: 2024/07/18 12:15:27 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_argc(t_data *data, int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || fd < 0)
	{
		ft_printf("Error\nInvalid map\n");
		free(data);
		exit(EXIT_FAILURE);
	}
	if (!ft_strnstr(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4))
	{
		ft_printf("Error\nNeed a <.ber> file\n");
		free(data);
		exit(EXIT_FAILURE);
	}
	data->size_x = (ft_line_length(fd) * IMG_W);
	data->size_y = (ft_count_lines(fd, data->size_x, IMG_W) * IMG_H);
	data->movement = 0;
	data->obj = 0;
	data->poison = 0;
	data->c_acces = 0;
	data->exit_found = 0;
	close(fd);
}

static void	check_characters(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->size_y / IMG_H)
	{
		x = 0;
		while (x < data->size_x / IMG_W)
		{
			if (data->map[y][x] != '0' && data->map[y][x] != '1'
				&& data->map[y][x] != 'C' && data->map[y][x] != 'E'
				&& data->map[y][x] != 'P' && data->map[y][x] != 'R')
				error_msg("Error\nInvalid character in map", data);
			x++;
		}
		y++;
	}
}

static void	check_count(t_data *data)
{
	int	x;
	int	y;
	int	exit_count;
	int	player_count;

	exit_count = 0;
	player_count = 0;
	y = 0;
	while (y < data->size_y / IMG_H)
	{
		x = 0;
		while (x < data->size_x / IMG_W)
		{
			if (data->map[y][x] == 'E')
				exit_count++;
			else if (data->map[y][x] == 'C')
				data->poison++;
			else if (data->map[y][x] == 'P')
				player_count++;
			x++;
		}
		y++;
	}
	if (exit_count != 1 || data->poison < 1 || player_count != 1)
		error_msg("Error\nMap must contain one E, min. one C and one P", data);
}

static void	check_walls_rectangular(t_data *data)
{
	int		x;
	int		y;
	size_t	row_length;

	row_length = ft_strlen(data->map[0]);
	x = 0;
	while (x < data->size_x / IMG_W)
	{
		if (data->map[0][x] != '1' || data->map[data->size_y / IMG_H
			- 1][x] != '1')
			error_msg("Error\nMap is not closed by walls", data);
		x++;
	}
	y = 0;
	while (y < data->size_y / IMG_H)
	{
		if (data->map[y][0] != '1' || data->map[y][data->size_x / IMG_W
			- 1] != '1')
			error_msg("Error\nMap is not closed by walls", data);
		if (ft_strlen(data->map[y]) != row_length)
			error_msg("Error\nMap is not rectangular", data);
		y++;
	}
}

void	check_map(t_data *data)
{
	check_characters(data);
	check_count(data);
	check_walls_rectangular(data);
}
