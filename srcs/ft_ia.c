/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 21:54:48
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-07 16:28:28
*/

#include "ft_ia.h"

void ft_ia_play(t_game *game, t_player player)
{
	int i, j;

	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].owner == player)
			{
				t_dir dir = ft_ia_closer_town_get(game, i, j);
				printf("tile %d %d => dir %d", i, j, dir);

				switch (dir)
				{
					case DIR_UP:
						if (ft_tile_is_able_to_move(game, i, j, i, j-1, player))
						{
							ft_tile_surroundings_try_conquer(game, i, j-1, player);
							game->map[j-1][i].lastMove = game->turn;
							game->currentPlayerMovesLeft--;
						}
						break;
					case DIR_DOWN:
						if (ft_tile_is_able_to_move(game, i, j, i, j+1, player))
						{
							ft_tile_surroundings_try_conquer(game, i, j+1, player);
							game->map[j+1][i].lastMove = game->turn;
							game->currentPlayerMovesLeft--;
						}
						break;
					case DIR_LEFT:
						if (ft_tile_is_able_to_move(game, i, j, i-1, j, player))
						{
							ft_tile_surroundings_try_conquer(game, i-1, j, player);
							game->map[j][i-1].lastMove = game->turn;
							game->currentPlayerMovesLeft--;
						}
						break;
					case DIR_RIGHT:
						if (ft_tile_is_able_to_move(game, i, j, i+1, j, player))
						{
							ft_tile_surroundings_try_conquer(game, i+1, j, player);
							game->map[j][i+1].lastMove = game->turn;
							game->currentPlayerMovesLeft--;
						}
						break;
					default:
						printf("caca %s %d\n", __FILE__, __LINE__);
						break;
				}
			}
		}
	}		
}


t_dir ft_ia_closer_town_get(t_game *game, int x, int y)
{
	int i, j;
	int dist = (NB_TILE_X * NB_TILE_Y) * (NB_TILE_X * NB_TILE_Y);
	int newx, newy;
	
	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].type == TILE_TOWN)
			{
				int dx = x-i, dy = y-j;

				if (dx*dx + dy*dy < dist)
					newx = i, newy = j, dist = dx*dx + dy*dy;
			}
		}
	}

	if (newx < x)
		return DIR_LEFT;
	else if (newx > x)
		return DIR_RIGHT;
	else if (newy < y)
		return DIR_UP;
	else if (newy > y)
		return DIR_DOWN;
	else
		return DIR_LAST;
}

