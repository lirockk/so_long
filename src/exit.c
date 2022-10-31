/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:29:06 by ademurge          #+#    #+#             */
/*   Updated: 2022/10/31 17:18:20 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_map_sqr(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->width)
	{
		j = -1;
		while (++j < game->length)
			mlx_destroy_image(game->mlx, game->map_sqr[i][j].img);
	}
}

void	free_map(t_game *game)
{
	int	i;

	i = -1;
	while (game->map && game->map[++i])
		free(game->map[i]);
	if (game->map)
		free(game->map);
}

void	ft_error(char *type, t_game *game)
{
	char	*join;

	join = "Error : ";
	join = ft_strjoin(join, type);
	ft_putendl_fd(join, STDERR_FILENO);
	free(join);
	end_game(game, EXIT_FAILURE);
}

int	end_game(t_game *game, int type_exit)
{
	if (game)
	{
		if (game->is_mlx == YES)
		{
			mlx_destroy_window(game->mlx, game->win);
			free_map_sqr(game);
		}
		free_map(game);
	}
	exit(type_exit);
}