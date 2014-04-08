/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 21:54:48
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-09 01:22:35
*/

#include "ft_ia.h"

void ft_ia_play(t_game *game, t_player player)
{
	int i, j;

	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].owner == player && game->map[j][i].units > 0)
			{
				int max = -1;

				int up = ft_tile_move(game, i, j, i, j-1, player, true);
				int down = ft_tile_move(game, i, j, i, j+1, player, true);
				int left = ft_tile_move(game, i, j, i-1, j, player, true);
				int right = ft_tile_move(game, i, j, i+1, j, player, true);

				if (up > max)
					max = up;
				if (down > max)
					max = down;
				if (left > max)
					max = left;
				if (right > max)
					max = right;
				
printf("p=%d - %d %d %d %d\n", player, up, down, left, right);

				if (max == up)
					ft_tile_move(game, i, j, i, j-1, player, false);
				else if (max == down)
					ft_tile_move(game, i, j, i, j+1, player, false);
				else if (max == left)
					ft_tile_move(game, i, j, i-1, j, player, false);
				else if (max == right)
					ft_tile_move(game, i, j, i+1, j, player, false);
				else
					;
			}
		}
	}		
}


/*
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

int ft_ia_game_eval(t_game *game, t_player player)
{
	int i, j;
	int score = 0;

	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].owner == player)
			{
				score += ft_tile_score_get(game->map[j][i].type);
			}
		}
	}

	return score;
}
*/

