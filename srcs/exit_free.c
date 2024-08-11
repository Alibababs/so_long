/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:27:18 by pbailly           #+#    #+#             */
/*   Updated: 2024/08/11 13:50:46 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(char *message, t_data *data)
{
	{
		ft_printf(message);
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

void	ft_lose(t_data *data)
{
	ft_printf("Giving up already?\n");
	free_data(data);
	exit(EXIT_SUCCESS);
}

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

void	free_data(t_data *data)
{
	if (data)
	{
		free_map(data->map);
		if (data->obj || data->background || data->player || data->text_box)
			free_images(data);
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
