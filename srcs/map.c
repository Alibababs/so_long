/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:47:31 by pbailly           #+#    #+#             */
/*   Updated: 2024/07/17 15:57:16 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_create_map(t_data *data)
{
	data->x = 0;
	data->y = 0;
	while (data->y < (data->size_y / IMG_H))
	{
		if (data->map[data->y][data->x] == 'P')
			init_player(data, "./textures/player.xpm");
		else if (data->map[data->y][data->x] == '1')
			init_obj(data, "./textures/wall.xpm");
		else if (data->map[data->y][data->x] == 'C')
			init_obj(data, "./textures/collect.xpm");
		else if (data->map[data->y][data->x] == 'E')
			init_obj(data, "./textures/exit.xpm");
		else if (data->map[data->y][data->x] == 'R')
			init_obj(data, "./textures/enemy.xpm");
		if (data->x < (data->size_x / IMG_W))
			data->x++;
		else
		{
			data->y++;
			data->x = 0;
		}
	}
}

void	load_map(t_data *data, char *filename)
{
	int		fd;
	int		y;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_msg("Error\nUnable to open map file", data);
	data->map = malloc((data->size_y / IMG_H + 1) * sizeof(char *));
	if (!data->map)
		error_msg("Error\nError allocating", data);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		data->map[y++] = (line);
		line = get_next_line(fd);
	}
	data->map[y] = NULL;
	if (y == 0)
		error_msg("Error\nMap file is empty", data);
	close(fd);
}
