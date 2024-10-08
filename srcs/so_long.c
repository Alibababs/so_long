/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:44:26 by alibabab          #+#    #+#             */
/*   Updated: 2024/08/11 15:40:53 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(char *message, t_data *data)
{
	ft_printf(message);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	ft_exit_success(char *message, t_data *data)
{
	ft_printf(message);
	free_data(data);
	exit(EXIT_SUCCESS);
}

static int	cross(t_data *data)
{
	ft_exit_success("Giving up already ?\n", data);
	return (0);
}

static void	all(t_data *data, char **argv)
{
	load_map(data, argv[1]);
	init_background(data);
	ft_create_map(data);
	init_text_box(data);
	check_map(data);
	path_checker(data);
	mlx_hook(data->win, 17, 0, cross, data);
	mlx_hook(data->win, 02, (1L << 0), touch, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error_msg("Error\nmalloc failed\n", data);
	check_argc(data, argc, argv);
	data->mlx = mlx_init();
	if (!data->mlx)
		error_msg("Error\nFailed to initialize mlx\n", data);
	data->win = mlx_new_window(data->mlx, data->size_x, data->size_y,
			"The Witchcat 3 : Wild hunt");
	if (!data->win)
		error_msg("Error\nFailed to initialize window\n", data);
	all(data, argv);
	free_data(data);
	exit(EXIT_FAILURE);
}
