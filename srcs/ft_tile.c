/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-10 14:09:23
*/

#include "ft_tile.h"


void ft_tile_selected_update(t_game *game)
{
	if (game->isATileSelected == 1)
	{
		// move 
		if (ft_tile_move(game, game->selected.x, game->selected.y,
						game->mouse.x/50, game->mouse.y/50,
						OWNER_PLAYER_1, false) != -1)
		{
			game->map[game->mouse.y/50][game->mouse.x/50].lastMove = game->turn;	
			game->currentPlayerMovesLeft--;
		}

		game->isATileSelected = 0;
	}
	// select
	else if (game->isATileSelected == 0)
	{
		game->selected.x = game->mouse.x/50;
		game->selected.y = game->mouse.y/50;

		game->isATileSelected = 1;
	}
	// unselect
	else
	{
		game->isATileSelected = 0;
	}
}

int ft_tile_is_able_to_move(t_game *game, int oldX, int oldY, int newX, int newY, t_player player)
{
	/* move if :
		the old and new tiles are !=
		the old tile is owned by the player
		there are units on the old tile
		the player have non zero moves left
		the old tile has not moved yet
		the old tile is on the map
		the new tile is on teh map
		distance is equal or less than 2
	*/
	if ((oldX != newX || oldY != newY)
		&& game->map[oldY][oldX].owner == player
		&& game->map[oldY][oldX].units > 0
		&& game->currentPlayerMovesLeft > 0
		&& game->map[oldY][oldX].lastMove < game->turn
		&& ft_tile_is_on_map(oldX, oldY)
		&& ft_tile_is_on_map(newX, newY)
		&& pow(newX - oldX, 2) + pow(newY - oldY, 2) <= 2*2)
		return 1;
	else
		return 0;
}

int ft_tile_is_able_to_be_annexed(t_game *game, int x, int y)
{
	// tile is on map && tile is empty
	// tile is land or sea (ie not town or capital)
	if (ft_tile_is_on_map(x, y) && game->map[y][x].units == 0
		&& (game->map[y][x].type == TILE_LAND || game->map[y][x].type == TILE_SEA))
		return 1;
	else
		return 0;
}

int ft_tile_is_on_map(int x, int y)
{
	return (x >= 0 && x < NB_TILE_X && y >= 0 && y < NB_TILE_Y);
}

int ft_tile_surroundings_one_try_annexe(t_game *game, int x, int y, t_player player, t_bool simulate)
{
	int score = 0;

	if (ft_tile_is_able_to_be_annexed(game, x, y))
	{
		if (game->map[y][x].owner != player)
			score += ft_tile_score_get(game->map[y][x].type);

		if (!simulate)
			game->map[y][x].owner = player;
	}

	return score;
}

int ft_tile_surroundings_all_try_annexe(t_game *game, int x, int y, t_player player, t_bool simulate)
{
	int score = 0;

	// up line
	score += ft_tile_surroundings_one_try_annexe(game, x-1, y-1, player, simulate);
	score += ft_tile_surroundings_one_try_annexe(game, x, y-1, player, simulate);
	score += ft_tile_surroundings_one_try_annexe(game, x+1, y-1, player, simulate);

	// left and right
	score += ft_tile_surroundings_one_try_annexe(game, x-1, y, player, simulate);
	score += ft_tile_surroundings_one_try_annexe(game, x+1, y, player, simulate);

	// down line
	score += ft_tile_surroundings_one_try_annexe(game, x-1, y+1, player, simulate);
	score += ft_tile_surroundings_one_try_annexe(game, x, y+1, player, simulate);
	score += ft_tile_surroundings_one_try_annexe(game, x+1, y+1, player, simulate);

	return score;
}


int ft_tile_move(t_game *game, int srcx, int srcy, int destx, int desty, t_player player, t_bool simulate)
{
	int success = 0;
	t_tile *old = &game->map[srcy][srcx];
	t_tile *new = &game->map[desty][destx];
	t_player newOwner = new->owner;

	if (!ft_tile_is_able_to_move(game, srcx, srcy, destx, desty, player))
		return -1;

	// conquer new land or move unit
	if (new->owner == OWNER_NONE || new->owner == player)
	{
		if (!simulate)
		{
			new->owner = player;
			while (new->units < 99 && old->units > 0)
			{
				new->units ++;
				old->units --;
			}
		}
		success = 1;
	}
	// attack
	else
	{
		// attack win
		if (old->units > new->units)
		{
			if (!simulate)
			{
				new->owner = player;
				new->units = old->units - new->units;
				old->units = 0;
			}
			success = 1;
		}
		// attack lost
		else
		{
			if (!simulate)
			{
				new->units -= old->units;
				old->units = 0;
			}
			success = 0;
		}
	}

	int ret = 0;

	if (success)
	{
		if (newOwner != player)
			ret += ft_tile_score_get(new->type);
		ret += ft_tile_surroundings_all_try_annexe(game, destx, desty, player, simulate);	
	}

	return ret;
}

int ft_tile_score_get(t_tile_type tile)
{
	int ret = 0;

	switch (tile)
	{
		case TILE_SEA:
			ret = 1;
			break;
		case TILE_LAND:
			ret = 5;
			break;
		case TILE_TOWN:
			ret = 25;
			break;
		case TILE_CAPITAL:
			ret = 50;
			break;

		default:
			printf("Erreur switch : case not handled. %s %d - info : %d\n", __FILE__, __LINE__, tile);
			break;
	}

	return ret;
}

int ft_tile_is_in_surroundings(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_tile_type tile)
{
	// up line
	if (ft_tile_is_on_map(x-1, y-1) && map[y-1][x-1].type == tile)
		return 1;
	if (ft_tile_is_on_map(x, y-1) && map[y-1][x].type == tile)
		return 1;
	if (ft_tile_is_on_map(x+1, y-1) && map[y-1][x+1].type == tile)
		return 1;

	// left and right
	if (ft_tile_is_on_map(x-1, y) && map[y][x-1].type == tile)
		return 1;
	if (ft_tile_is_on_map(x+1, y) && map[y][x+1].type == tile)
		return 1;

	// down line
	if (ft_tile_is_on_map(x-1, y+1) && map[y+1][x-1].type == tile)
		return 1;
	if (ft_tile_is_on_map(x, y+1) && map[y+1][x].type == tile)
		return 1;
	if (ft_tile_is_on_map(x+1, y+1) && map[y+1][x+1].type == tile)
		return 1;

	return 0;
}

void ft_tile_blit(SDL_Renderer *ren, t_data *data, t_tile *tile)
{
	char s[1024];
	t_vector blitPos = {tile->pos.x*50, tile->pos.y*50};

	/* tile background */
	if (tile->type >= TILE_LAST)
		printf("Erreur ft_tile_blit() : unknown id %d. %s %d\n", tile->type, __FILE__, __LINE__);
	else
		ft_sdl_texture_blit(ren, data->tile[tile->type], blitPos.x, blitPos.y);

	/* nb units */
	if (tile->units != 0)
	{
		sprintf(s, "%d", tile->units);

		ft_sdl_text_blit(ren, data->font, s, blitPos.x+50/2, blitPos.y+50/2,
							ALIGN_CENTER, ALIGN_CENTER, 0, 0, 0);
	}
}

int ft_tile_need_edge(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_dir dir)
{
	int destx = x, desty = y;

	if (dir == DIR_UP)
		desty--;
	else if (dir == DIR_DOWN)
		desty++;
	else if (dir == DIR_LEFT)
		destx--;
	else if (dir == DIR_RIGHT)
		destx++;
	else
		printf("Erreur ft_tile_need_edge() : unknown dir %d=%s. %s %d\n", dir, strDir[dir], __FILE__, __LINE__);

	if (ft_tile_is_on_map(x, x)
		&& map[y][x].owner != map[desty][destx].owner
		&& map[y][x ].owner != OWNER_NONE)
		return 1;
	else
		return 0;
}

void ft_tile_owner_blit(SDL_Renderer *ren, t_data *data, t_tile *tile, t_dir dir)
{
	t_vector blitPos = {tile->pos.x*50, tile->pos.y*50};

	SDL_SetTextureColorMod(data->edge[dir], playerColors[tile->owner][0],
										playerColors[tile->owner][1],
										playerColors[tile->owner][2]);
	SDL_SetTextureAlphaMod(data->edge[dir], 192);
	ft_sdl_texture_blit(ren, data->edge[dir], blitPos.x, blitPos.y);
}
