/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:51:33 by ademurge          #+#    #+#             */
/*   Updated: 2022/10/31 18:48:40 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	replace_sqr(t_game *game, int x, int y, char *xpm_file)
{
	mlx_destroy_image(game->mlx, game->map_sqr[y][x].img);
	game->map_sqr[y][x].img = mlx_xpm_file_to_image(game->mlx, xpm_file,
			&game->sqr_size, &game->sqr_size);
	mlx_put_image_to_window(game->mlx, game->win, game->map_sqr[y][x].img,
		x * 80, y * 80);
}

void	move_or_not(t_game *game, int x, int y, char *direction)
{
	if (game->map[y][x] == WALL)
		return ;
	else if (game->map[y][x] == BACKGROUND)
		move_player(game, x, y, direction);
	else if (game->map[y][x] == EXIT && game->exit_status == OPEN)
	{
		ft_printf("*******   YOU WIN   *******\n");
		end_game(game, EXIT_SUCCESS);
	}
	else if (game->map[y][x] == ITEM)
	{
		game->nb_items--;
		move_player(game, x, y, direction);
		if (!game->nb_items && game->exit_status == CLOSED)
		{
			game->exit_pos = ft_find_pos(game, EXIT);
			replace_sqr(game, game->exit_pos.x, game->exit_pos.y,
				OPEN_EXIT_XPM);
			game->exit_status = OPEN;
		}
	}
	else if (game->map[y][x] == GHOST)
	{
		ft_printf("*******   GAME OVER   *******\n");
		end_game(game, EXIT_SUCCESS);
	}
}

void	move_player(t_game *game, int new_x, int new_y, char *direction)
{
	int	x;
	int	y;

	x = game->player_pos.x;
	y = game->player_pos.y;
	replace_sqr(game, x, y, BACKGROUND_XPM);
	if (!ft_strcmp(direction, MV_UP))
		replace_sqr(game, new_x, new_y, PL_UP_XPM);
	else if (!ft_strcmp(direction, MV_DOWN))
		replace_sqr(game, new_x, new_y, PL_DOWN_XPM);
	else if (!ft_strcmp(direction, MV_LEFT))
		replace_sqr(game, new_x, new_y, PL_LEFT_XPM);
	else if (!ft_strcmp(direction, MV_RIGHT))
		replace_sqr(game, new_x, new_y, PL_RIGHT_XPM);
	game->map[y][x] = BACKGROUND;
	game->map[new_y][new_x] = PLAYER;
	game->player_pos.x = new_x;
	game->player_pos.y = new_y;
	ft_printf("Move %s |  Total of moves : %i\n", direction, ++game->nb_move);
}

void	start_game(t_game *game)
{
	init_mlx(game);
	init_map_sqr(game);
	game->player_pos = init_game(game);
	draw_map(game);
	controls (game);
}
