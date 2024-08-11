/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:47:31 by pbailly           #+#    #+#             */
/*   Updated: 2024/08/11 18:51:26 by alibaba          ###   ########.fr       */
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

	data->map = malloc((data->size_y / IMG_H + 1) * sizeof(char *));
	if (!data->map)
		error_msg("Error\nError allocating\n", data);
	y = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_msg("Error\nUnable to open map file\n", data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		data->map[y++] = (line);
		line = get_next_line(fd);
	}
	data->map[y] = NULL;
	if (close(fd) < 0)
		error_msg("Error\nFailed to close file\n", data);
	if (y == 0)
		error_msg("Error\nMap file is empty\n", data);
}

int	ft_line_length(int fd, t_data *data)
{
	char	buffer[1];
	int		length;
	int		bytes;

	buffer[0] = '\0';
	bytes = 1;
	length = 0;
	while (bytes == 1)
	{
		bytes = read(fd, buffer, 1);
		if (buffer[0] != '\n')
			length++;
		else
			break ;
	}
	if (length == 0)
		error_msg("Error\nEmpty line\n", data);
	return (length);
}

int	ft_count_lines(int fd, int x, int img_w, t_data *data)
{
	char	*line;
	int		linecount;

	linecount = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if ((int)ft_strlen(line) < x / img_w || (ft_strlen(line) == 1
				&& *line != '\n'))
		{
			free(line);
			if (close(fd) < 0)
				error_msg("Error\nFailed to close file\n", data);
			error_msg("Error\nMap is not rectangular\n", data);
		}
		else
		{
			free(line);
			linecount++;
		}
	}
	return (linecount);
}
