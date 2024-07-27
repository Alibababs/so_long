/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:34:30 by pbailly           #+#    #+#             */
/*   Updated: 2024/07/27 18:14:05 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	{
		ft_printf("Error\nEmpty line\n");
		free(data);
		exit(EXIT_FAILURE);
	}
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
			free(data);
			ft_printf("Error\nEmpty line or first line too long\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			free(line);
			linecount++;
		}
	}
	return (linecount);
}
