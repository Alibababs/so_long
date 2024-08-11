/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:27:18 by pbailly           #+#    #+#             */
/*   Updated: 2024/08/11 16:57:12 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

static void	free_images(t_data *data)
{
	if (data->background)
	{
		mlx_destroy_image(data->mlx, data->background);
		data->background = NULL;
	}
	if (data->obj)
	{
		mlx_destroy_image(data->mlx, data->obj);
		data->obj = NULL;
	}
	if (data->player)
	{
		mlx_destroy_image(data->mlx, data->player);
		data->player = NULL;
	}
	if (data->text_box)
	{
		mlx_destroy_image(data->mlx, data->text_box);
		data->text_box = NULL;
	}
}

static void	free_visited(t_data *data)
{
	int	i;

	if (data && data->visited)
	{
		i = 0;
		while (i < data->size_y / IMG_H)
		{
			free(data->visited[i]);
			i++;
		}
		free(data->visited);
		data->visited = NULL;
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->map)
			free_map(data->map);
		if (data->obj || data->background || data->player || data->text_box)
			free_images(data);
		if (data->visited)
			free_visited(data);
		if (data->win)
		{
			mlx_destroy_window(data->mlx, data->win);
			data->win = NULL;
		}
	}
	if (data && data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data);
}
