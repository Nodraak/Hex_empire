/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 21:54:48
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 22:23:58
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
				switch (rand()%4)
				{
					// up
					case 0:
						if (ft_tile_is_able_to_move(game, i, j, i, j-1, player))
						{
							int ret = ft_tile_move(&game->map[j][i], &game->map[j-1][i], player);
							// move succesfully
							if (ret == 2)
								ft_tile_surroundings_try_conquer(game, i, j-1, player);
							// move but perhaps failed in conquering new tile
							if (ret)
							{
								game->map[j-1][i].lastMove = game->turn;	
								game->currentPlayerMovesLeft--;
							}
						}
						break;
					// down
					case 1:
						if (ft_tile_is_able_to_move(game, i, j, i, j+1, player))
						{
							int ret = ft_tile_move(&game->map[j][i], &game->map[j+1][i], player);
							// move succesfully
							if (ret == 2)
								ft_tile_surroundings_try_conquer(game, i, j+1, player);
							// move but perhaps failed in conquering new tile
							if (ret)
							{
								game->map[j+1][i].lastMove = game->turn;	
								game->currentPlayerMovesLeft--;
							}
						}
						break;
					// left
					case 2:
						if (ft_tile_is_able_to_move(game, i, j, i-1, j, player))
						{
							int ret = ft_tile_move(&game->map[j][i], &game->map[j][i-1], player);
							// move succesfully
							if (ret == 2)
								ft_tile_surroundings_try_conquer(game, i-1, j, player);
							// move but perhaps failed in conquering new tile
							if (ret)
							{
								game->map[j][i-1].lastMove = game->turn;	
								game->currentPlayerMovesLeft--;
							}
						}
						break;
					// right
					case 3:
						if (ft_tile_is_able_to_move(game, i, j, i+1, j, player))
						{
							int ret = ft_tile_move(&game->map[j][i], &game->map[j][i+1], player);
							// move succesfully
							if (ret == 2)
								ft_tile_surroundings_try_conquer(game, i+1, j, player);
							// move but perhaps failed in conquering new tile
							if (ret)
							{
								game->map[j][i+1].lastMove = game->turn;	
								game->currentPlayerMovesLeft--;
							}
						}
						break;
				}
			}
		}
	}		
}
