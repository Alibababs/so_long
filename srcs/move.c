/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 00:09:05 by alibabab          #+#    #+#             */
/*   Updated: 2024/08/11 14:43:36 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	touch(int keycode, t_data *data)
{
	if (keycode == 65307)
		ft_exit_success("Giving up already ?\n", data);
	else if (keycode == 'w' || keycode == 65362)
		move(data, 'y', UP);
	else if (keycode == 'a' || keycode == 65361)
		move(data, 'x', LEFT);
	else if (keycode == 's' || keycode == 65364)
		move(data, 'y', DOWN);
	else if (keycode == 'd' || keycode == 65363)
		move(data, 'x', RIGHT);
	if (data->map[data->p_y][data->p_x] == 'E')
	{
		ft_printf("Congrats! You managed to kill yourself!\n");
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (data->map[data->p_y][data->p_x] == 'R')
	{
		ft_printf("The witch hunters have caught you!\n");
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static void	count(t_data *data)
{
	char	*str;

	mlx_put_image_to_window(data->mlx, data->win, data->text_box, 0, 0);
	str = ft_itoa(data->movement);
	mlx_string_put(data->mlx, data->win, 24, 25, 0xDCDCDC, "Movements: ");
	mlx_string_put(data->mlx, data->win, 90, 26, 0xDCDCDC, str);
	free(str);
}

static void	position(t_data *data, char pos, int dir)
{
	mlx_put_image_to_window(data->mlx, data->win, data->background, (data->p_x
			* IMG_W), (data->p_y * IMG_H));
	if ((pos == 'y' && data->map[data->p_y + 1 * dir][data->p_x] != '1')
		&& (data->map[data->p_y + 1 * dir][data->p_x] != 'E'))
	{
		ft_printf("You moved %d times.\n", ++data->movement);
		data->p_y = data->p_y + 1 * dir;
	}
	else if ((pos == 'x' && data->map[data->p_y][data->p_x + 1 * dir] != '1')
		&& (data->map[data->p_y][data->p_x + 1 * dir] != 'E'))
	{
		ft_printf("You moved %d times.\n", ++data->movement);
		data->p_x = data->p_x + 1 * dir;
	}
}

static void	collect(t_data *data, int *collected)
{
	if (data->map[data->p_y][data->p_x] == 'C')
	{
		(*collected)++;
		data->map[data->p_y][data->p_x] = '0';
	}
}

void	move(t_data *data, char pos, int dir)
{
	static int	collected = 0;

	position(data, pos, dir);
	if ((pos == 'y' && data->map[data->p_y + 1 * dir][data->p_x] == 'E')
		&& (collected == data->poison))
	{
		ft_printf("You moved %d times.\n", ++data->movement);
		data->p_y = data->p_y + 1 * dir;
	}
	else if ((pos == 'x' && data->map[data->p_y][data->p_x + 1 * dir] == 'E')
		&& (collected == data->poison))
	{
		ft_printf("You moved %d times.\n", ++data->movement);
		data->p_x = data->p_x + 1 * dir;
	}
	else if (((pos == 'y' && data->map[data->p_y + 1 * dir][data->p_x] == 'E')
		&& (collected != data->poison)) || ((pos == 'x'
		&& data->map[data->p_y][data->p_x + 1 * dir] == 'E')
		&& (collected != data->poison)))
		ft_printf("All poisons must be collected before making the potion.\n");
	mlx_put_image_to_window(data->mlx, data->win, data->player, (data->p_x
			* IMG_W), (data->p_y * IMG_H));
	collect(data, &collected);
	count(data);
}
