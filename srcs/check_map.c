/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:33:35 by pbailly           #+#    #+#             */
/*   Updated: 2024/08/11 17:03:56 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_argc(t_data *data, int argc, char **argv)
{
	int	fd;

	init_data(data);
	if (argc != 2)
		error_msg("Error\nExpected 2 arguments\n", data);
	if (!ft_strnstr(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4))
		error_msg("Error\nNeed a <.ber> extension\n", data);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_msg("Error\nCannot open file\n", data);
	data->size_x = (ft_line_length(fd, data) * IMG_W);
	data->size_y = (ft_count_lines(fd, data->size_x, IMG_W, data) * IMG_H);
	if (close(fd) < 0)
		error_msg("Error\nFailed to close file\n", data);
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
				error_msg("Error\nInvalid character in map\n", data);
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
		error_msg("Error\nMap must contain one E, one P, min. one C.\n", data);
}

static void	check_walls_rectangular(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->size_x / IMG_W)
	{
		if (data->map[0][x] != '1' || data->map[data->size_y / IMG_H
			- 1][x] != '1')
			error_msg("Error\nMap is not closed by walls\n", data);
		x++;
	}
	y = 0;
	while (y < data->size_y / IMG_H)
	{
		if (data->map[y][0] != '1' || data->map[y][data->size_x / IMG_W
			- 1] != '1')
			error_msg("Error\nMap is not closed by walls\n", data);
		if (ft_strlen(data->map[y]) != ft_strlen(data->map[0]))
			error_msg("Error\nMap is not rectangular\n", data);
		y++;
	}
}

void	check_map(t_data *data)
{
	check_walls_rectangular(data);
	check_count(data);
	check_characters(data);
}
