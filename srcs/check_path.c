/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:30:56 by alibaba           #+#    #+#             */
/*   Updated: 2024/08/11 15:33:38 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_valid_position(t_data *data, int x, int y, char initial)
{
	char	character;

	if (x < 0 || x >= data->size_x / IMG_W || y < 0 || y >= data->size_y
		/ IMG_H)
		return (false);
	if (data->visited[y][x] == 1)
		return (false);
	character = data->map[y][x];
	return (character == '0' || character == 'C' || character == initial
		|| character == 'P');
}

static bool	explore_map(t_data *data, int x, int y, char initial)
{
	if (!is_valid_position(data, x, y, initial))
		return (false);
	data->visited[y][x] = 1;
	if (data->map[y][x] == 'P')
		return (true);
	return (explore_map(data, x + 1, y, initial) || explore_map(data, x - 1, y,
			initial) || explore_map(data, x, y + 1, initial)
		|| explore_map(data, x, y - 1, initial));
}

static void	init_visited(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size_y / IMG_H)
	{
		j = 0;
		while (j < data->size_x / IMG_W)
		{
			data->visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	check_paths(t_data *data, char target, char *msg)
{
	int		x;
	int		y;
	bool	has_path;

	y = 0;
	while (y < data->size_y / IMG_H)
	{
		x = 0;
		while (x < data->size_x / IMG_W)
		{
			if (data->map[y][x] == target)
			{
				init_visited(data);
				has_path = explore_map(data, x, y, target);
				if (!has_path)
					error_msg(msg, data);
			}
			x++;
		}
		y++;
	}
}

void	path_checker(t_data *data)
{
	int	i;

	i = 0;
	data->visited = malloc((data->size_y / IMG_H) * sizeof(int *));
	if (!data->visited)
		error_msg("Error\nUnable to allocate memory for visited.\n", data);
	while (i < data->size_y / IMG_H)
	{
		data->visited[i] = malloc((data->size_x / IMG_W) * sizeof(int));
		if (!data->visited[i])
			error_msg("Error\nUnable to allocate memory for visited.\n", data);
		i++;
	}
	init_visited(data);
	if (!explore_map(data, data->p_x, data->p_y, 'P'))
		error_msg("Error\nNo valid path in the map\n", data);
	check_paths(data, 'C', "Error\nNo valid path to a collectible\n");
	check_paths(data, 'E', "Error\nNo valid path to an exit\n");
}
