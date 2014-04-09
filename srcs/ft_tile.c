/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-09 16:13:26
*/

#include "ft_tile.h"


void ft_tile_selected_update(t_game *game)
{
	
	if (game->isATileSelected == 1)
	{
		int dx = game->mouse.x/50 - game->selected.x;
		int dy = game->mouse.y/50 - game->selected.y;

		if (dx*dx + dy*dy <= 2*2)
		{
			// move 
			if (ft_tile_move(game, game->selected.x, game->selected.y,
							game->mouse.x/50, game->mouse.y/50,
							OWNER_PLAYER_1, false) != -1)
			{
				game->map[game->mouse.y/50][game->mouse.x/50].lastMove = game->turn;	
				game->currentPlayerMovesLeft--;
			}
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
	*/
	if ((oldX != newX || oldY != newY)
		&& game->map[oldY][oldX].owner == player
		&& game->map[oldY][oldX].units > 0
		&& game->currentPlayerMovesLeft > 0
		&& game->map[oldY][oldX].lastMove < game->turn
		&& ft_tile_is_on_map(oldX, oldY)
		&& ft_tile_is_on_map(newX, newY))
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
	switch (tile->type)
	{
		case TILE_SEA:
			ft_sdl_texture_blit(ren, data->blue, blitPos.x, blitPos.y);
			break;
		case TILE_TOWN:
		case TILE_CAPITAL:
			ft_sdl_texture_blit(ren, data->brown, blitPos.x, blitPos.y);
			break;
		case TILE_LAND:
			ft_sdl_texture_blit(ren, data->green, blitPos.x, blitPos.y);
			break;

		default:
			printf("Erreur switch : case not handled. %s %d\n", __FILE__, __LINE__);
			break;
	}

	/* owner */
	t_player i;

	for (i = OWNER_PLAYER_1; i < OWNER_PLAYER_LAST; ++i)
	{
		if (tile->owner == i)
		{
			SDL_SetTextureColorMod(data->mask, playerColors[i][0],
												playerColors[i][1],
												playerColors[i][2]);
			ft_sdl_texture_blit(ren, data->mask, blitPos.x, blitPos.y);
		}
	}

	/* nb units */
	if (tile->units != 0)
	{
		sprintf(s, "%d", tile->units);

		ft_sdl_text_blit(ren, data->font, s, tile->pos.x*50+50/2, tile->pos.y*50+50/2,
							ALIGN_CENTER, ALIGN_CENTER, 0, 0, 0);
	}
}


