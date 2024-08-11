/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:35 by alibabab          #+#    #+#             */
/*   Updated: 2024/08/11 17:01:06 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_data(t_data *data)
{
	data->movement = 0;
	data->obj = 0;
	data->poison = 0;
	data->c_acces = 0;
	data->exit_found = 0;
	data->player = 0;
	data->text_box = 0;
	data->background = 0;
	data->visited = 0;
	data->map = 0;
	data->win = 0;
	data->mlx = 0;
}

void	init_background(t_data *data)
{
	int		y;
	int		x;
	char	*path_img;
	int		img_width;
	int		img_height;

	path_img = "./textures/background.xpm";
	data->background = mlx_xpm_file_to_image(data->mlx, path_img, &img_width,
			&img_height);
	if (!data->background)
		error_msg("Error\nBackground image failed to load.", data);
	y = 0;
	while (y < data->size_y)
	{
		x = 0;
		while (x < data->size_x)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, x,
				y);
			x += IMG_W;
		}
		y += IMG_H;
	}
}

void	init_obj(t_data *data, char *path)
{
	int	img_width;
	int	img_height;

	if (data->obj)
		mlx_destroy_image(data->mlx, data->obj);
	data->obj = mlx_xpm_file_to_image(data->mlx, path, &img_width, &img_height);
	if (!data->obj)
		error_msg("Error\nImage failed to load.", data);
	mlx_put_image_to_window(data->mlx, data->win, data->obj, (data->x * IMG_W),
		(data->y * IMG_H));
}

void	init_player(t_data *data, char *path)
{
	int	img_width;
	int	img_height;

	data->p_x = data->x;
	data->p_y = data->y;
	if (data->player)
		mlx_destroy_image(data->mlx, data->player);
	data->player = mlx_xpm_file_to_image(data->mlx, path, &img_width,
			&img_height);
	if (!data->player)
		error_msg("Error\nPlayer image failed to load.", data);
	mlx_put_image_to_window(data->mlx, data->win, data->player, (data->x
			* IMG_W), (data->y * IMG_H));
}

void	init_text_box(t_data *data)
{
	int	img_width;
	int	img_height;

	data->text_box = mlx_xpm_file_to_image(data->mlx, "./textures/text_box.xpm",
			&img_width, &img_height);
	if (!data->text_box)
		error_msg("Error\nText box image failed to load.", data);
	mlx_put_image_to_window(data->mlx, data->win, data->text_box, 0, 0);
	mlx_string_put(data->mlx, data->win, 24, 25, 0xDCDCDC, "Movements:");
	mlx_string_put(data->mlx, data->win, 90, 26, 0xDCDCDC, "0");
}
