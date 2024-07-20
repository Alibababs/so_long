/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:44:30 by alibabab          #+#    #+#             */
/*   Updated: 2024/07/18 12:14:47 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define IMG_W 64
# define IMG_H 64

# define UP -1
# define DOWN 1
# define LEFT -1
# define RIGHT 1

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*background;
	void	*player;
	void	*text_box;
	void	*obj;
	char	**map;
	int		x;
	int		y;
	int		size_x;
	int		size_y;
	int		p_x;
	int		p_y;
	int		poison;
	int		movement;
	int		exit_found;
	int		c_acces;
	int		nb_collectibles;
}			t_data;

void		check_argc(t_data *data, int argc, char **argv);
void		check_map(t_data *data);

void		error_msg(char *message, t_data *data);
void		ft_lose(t_data *data);
void		free_data(t_data *data);

void		init_background(t_data *data);
void		init_player(t_data *data, char *path);
void		init_text_box(t_data *data);
void		init_obj(t_data *data, char *path);

void		ft_create_map(t_data *data);
void		load_map(t_data *data, char *filename);

int			touch(int keycode, t_data *data);
void		move(t_data *data, char pos, int dir);

int			ft_line_length(int fd);
int			ft_count_lines(int fd, int x, int img_w);

void		path_checker(t_data *data);

#endif
