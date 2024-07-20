/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:59:02 by pbailly           #+#    #+#             */
/*   Updated: 2024/07/20 16:49:27 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_player_position(t_data *data, t_point *player_pos)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->size_y / IMG_H)
	{
		x = 0;
		while (x < data->size_x / IMG_W)
		{
			if (data->map[y][x] == 'P')
			{
				player_pos->x = x;
				player_pos->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

static int	is_valid_move(t_data *data, int x, int y, int **visited)
{
	return (x >= 0 && y >= 0 && x < data->size_x / IMG_W && y < data->size_y
		/ IMG_H && data->map[y][x] != '1' && data->map[y][x] != 'R' && !visited[y][x]);
}

static void	explore_map(t_data *data, int x, int y, int **visited)
{
	if (!is_valid_move(data, x, y, visited))
		return ;
	visited[y][x] = 1;
	if (data->map[y][x] == 'C')
		data->c_acces++;
	if (data->map[y][x] == 'E')
		data->exit_found = 1;
	explore_map(data, x + 1, y, visited);
	explore_map(data, x - 1, y, visited);
	explore_map(data, x, y + 1, visited);
	explore_map(data, x, y - 1, visited);
}

static void	init_visited(t_data *data, int **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size_y / IMG_H)
	{
		visited[i] = malloc((data->size_x / IMG_W) * sizeof(int));
		j = 0;
		while (j < data->size_x / IMG_W)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	path_checker(t_data *data)
{
	t_point	player_pos;
	int		**visited;
	int		i;

	find_player_position(data, &player_pos);
	visited = malloc((data->size_y / IMG_H) * sizeof(int *));
	if (!visited)
		error_msg("Error\nUnable to allocate memory for visited.", data);
	init_visited(data, visited);
	explore_map(data, player_pos.x, player_pos.y, visited);
	i = 0;
	while (i < data->size_y / IMG_H)
		free(visited[i++]);
	free(visited);
	if (data->c_acces != data->poison || !data->exit_found)
		error_msg("Error\nNo valid path in the map", data);
}
