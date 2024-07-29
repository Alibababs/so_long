/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:59:02 by pbailly           #+#    #+#             */
/*   Updated: 2024/07/29 19:56:09 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_move(t_data *data, int x, int y, int **visited)
{
	return (x >= 0 && y >= 0 && x < data->size_x / IMG_W && y < data->size_y
		/ IMG_H && data->map[y][x] != '1' && data->map[y][x] != 'R'
		&& !visited[y][x]);
}

static void	explore_map(t_data *data, int x, int y, int **visited, int consider_exit)
{
	if (!is_valid_move(data, x, y, visited))
		return ;
	if (data->map[y][x] == 'E' && !consider_exit)
		return ;
	visited[y][x] = 1;
	if (data->map[y][x] == 'C')
		data->c_acces++;
	if (data->map[y][x] == 'E' && consider_exit)
		data->exit_found = 1;
	explore_map(data, x + 1, y, visited, consider_exit);
	explore_map(data, x - 1, y, visited, consider_exit);
	explore_map(data, x, y + 1, visited, consider_exit);
	explore_map(data, x, y - 1, visited, consider_exit);
}

static void	init_visited(t_data *data, int **visited, int init)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size_y / IMG_H)
	{
		if (init)
		{
			visited[i] = malloc((data->size_x / IMG_W) * sizeof(int));
			if (!visited[i])
				error_msg("Error\nUnable to allocate memory for visited.\n", data);
		}
		j = 0;
		while (j < data->size_x / IMG_W)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void check_collectibles(t_data *data, int **visited)
{
	int y;
	int x;

	y = 0;
	while (y < data->size_y / IMG_H)
	{
		x = 0;
		while (x < data->size_x / IMG_W)
		{
			if (data->map[y][x] == 'C')
			{
				data->c_acces = 0;
				init_visited(data, visited, 0);
				explore_map(data, x, y, visited, 0);
				if (data->c_acces == 0)
					error_msg("Error\nNo valid path to a collectible\n", data);
			}
			x++;
		}
		y++;
	}
}

void	path_checker(t_data *data)
{
	int		**visited;
	int		i;

	visited = malloc((data->size_y / IMG_H) * sizeof(int *));
	if (!visited)
		error_msg("Error\nUnable to allocate memory for visited.\n", data);
	init_visited(data, visited, 1);
	explore_map(data, data->p_x, data->p_y, visited, 1);
	check_collectibles(data, visited);
	i = 0;
	while (i < data->size_y / IMG_H)
		free(visited[i++]);
	free(visited);
	if (data->c_acces != data->poison || !data->exit_found)
		error_msg("Error\nNo valid path in the map\n", data);
}
