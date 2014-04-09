/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 21:54:48
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-09 14:24:43
*/

#include "ft_ia.h"

void ft_ia_play(t_game *game, t_player player)
{
	int i, j;

printf("\n==========\nIA PLAYER %d\n===========\n", player);

	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].owner == player && game->map[j][i].units > 0)
			{
printf("NEW MOVE\n==========\n");
				int max = 0;
				t_dir dir = DIR_NONE;
printf("--> simulate\n");
				int up = ft_tile_move(game, i, j, i, j-1, player, true);
				int down = ft_tile_move(game, i, j, i, j+1, player, true);
				int left = ft_tile_move(game, i, j, i-1, j, player, true);
				int right = ft_tile_move(game, i, j, i+1, j, player, true);

				if (up > max)
					max = up, dir = DIR_UP;
				if (down > max)
					max = down, dir = DIR_DOWN;
				if (left > max)
					max = left, dir = DIR_LEFT;
				if (right > max)
					max = right, dir = DIR_RIGHT;
printf("--> summary\np=%d tile %d %d - up=%d down=%d left=%d right=%d\n", player, i, j, up, down, left, right);
printf("--> real move\ndir=%s\n", strDir[dir]);
				
				if (max == up && ft_tile_move(game, i, j, i, j-1, player, false) != -1)
				{
					game->map[j-1][i].lastMove = game->turn;	
					game->currentPlayerMovesLeft--;
				}
				else if (max == down && ft_tile_move(game, i, j, i, j+1, player, false) != -1)
				{
					game->map[j+1][i].lastMove = game->turn;	
					game->currentPlayerMovesLeft--;
				}
				else if (max == left && ft_tile_move(game, i, j, i-1, j, player, false) != -1)
				{
					game->map[j][i-1].lastMove = game->turn;	
					game->currentPlayerMovesLeft--;
				}
				else if (max == right && ft_tile_move(game, i, j, i+1, j, player, false) != -1)
				{
					game->map[j][i+1].lastMove = game->turn;	
					game->currentPlayerMovesLeft--;
				}
				else
					printf("no dir found, abort move\n");
			}
		}
	}
	printf("\n\n\n");
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

