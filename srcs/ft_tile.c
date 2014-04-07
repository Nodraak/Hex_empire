/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-07 11:34:40
*/

#include "ft_tile.h"


void ft_tile_selected_update(t_game *game)
{
	
	if (ft_tile_is_able_to_move(game, game->selected.x, game->selected.y,
								game->mouse.x/50, game->mouse.y/50, OWNER_PLAYER_1)
		&& game->isATileSelected == 1)
	{
		int dx = game->mouse.x/50 - game->selected.x;
		int dy = game->mouse.y/50 - game->selected.y;

		if (dx*dx + dy*dy <= 2*2)
		{
			int ret = ft_tile_move(&game->map[game->selected.y][game->selected.x],
							&game->map[game->mouse.y/50][game->mouse.x/50],
							OWNER_PLAYER_1);
			// move succesfully
			if (ret == 2)
				ft_tile_surroundings_try_conquer(game, game->mouse.x/50, game->mouse.y/50, OWNER_PLAYER_1);
			// move but perhaps failed in conquering new tile
			if (ret)
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
		&& game->map[oldY][oldX].units != 0
		&& game->currentPlayerMovesLeft > 0
		&& game->map[oldY][oldX].lastMove < game->turn
		&& oldX >= 0 && oldX < NB_TILE_X && oldY >= 0 && oldY < NB_TILE_Y
		&& newX >= 0 && newX < NB_TILE_X && newY >= 0 && newY < NB_TILE_Y)
		return 1;
	else
		return 0;
}

int ft_tile_is_able_to_be_conquered(t_game *game, int x, int y)
{
	// tile is on map
	if (x >= 0 && x < NB_TILE_X && y >= 0 && y < NB_TILE_Y)
	{
		// tile is empty
		if (game->map[y][x].units == 0)
		{
			// tile is land or sea
			if (game->map[y][x].type == TILE_LAND || game->map[y][x].type == TILE_SEA)
			{
				return 1;
			}
		}
	}

	return 0;
}

void ft_tile_surroundings_try_conquer(t_game *game, int x, int y, t_player player)
{
	// up line
	if (ft_tile_is_able_to_be_conquered(game, x-1, y-1))
		game->map[y-1][x-1].owner = player;
	if (ft_tile_is_able_to_be_conquered(game, x, y-1))
		game->map[y-1][x].owner = player;
	if (ft_tile_is_able_to_be_conquered(game, x+1, y-1))
		game->map[y-1][x+1].owner = player;

	// left and right
	if (ft_tile_is_able_to_be_conquered(game, x-1, y))
		game->map[y][x-1].owner = player;
	if (ft_tile_is_able_to_be_conquered(game, x+1, y))
		game->map[y][x+1].owner = player;

	// down line
	if (ft_tile_is_able_to_be_conquered(game, x-1, y+1))
		game->map[y+1][x-1].owner = player;
	if (ft_tile_is_able_to_be_conquered(game, x, y+1))
		game->map[y+1][x].owner = player;
	if (ft_tile_is_able_to_be_conquered(game, x+1, y+1))
		game->map[y+1][x+1].owner = player;
}


int ft_tile_move(t_tile *old, t_tile *new, t_player player)
{
	// conquer new land or move unit
	if (new->owner == OWNER_NONE || new->owner == player)
	{
		new->owner = player;
		while (new->units < 99 && old->units > 0)
		{
			new->units ++;
			old->units --;
		}

		return 2;
	}
	// attack
	else if (new->owner != player && new->owner != OWNER_NONE)
	{
		// attack win
		if (old->units > new->units)
		{
			new->owner = player;
			new->units = old->units - new->units;
			old->units = 0;

			return 2;
		}
		// attack lost
		else
		{
			new->units -= old->units;
			old->units = 0;

			return 1;
		}
	}
	else
		printf("dont know what to do %s %d\n", __FILE__, __LINE__);

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
	if (tile->owner == OWNER_PLAYER_1)
	{
		SDL_SetTextureColorMod(data->mask, 0, 0, 128); // blue
		ft_sdl_texture_blit(ren, data->mask, blitPos.x, blitPos.y);
	}
	if (tile->owner == OWNER_PLAYER_2)
	{
		SDL_SetTextureColorMod(data->mask, 128, 0, 0); // red
		ft_sdl_texture_blit(ren, data->mask, blitPos.x, blitPos.y);
	}
	if (tile->owner == OWNER_PLAYER_3)
	{
		SDL_SetTextureColorMod(data->mask, 200, 200, 0); // yellow
		ft_sdl_texture_blit(ren, data->mask, blitPos.x, blitPos.y);
	}
	if (tile->owner == OWNER_PLAYER_4)
	{
		SDL_SetTextureColorMod(data->mask, 128, 0, 128); // magenta
		ft_sdl_texture_blit(ren, data->mask, blitPos.x, blitPos.y);
	}

	/* nb units */
	if (tile->units != 0)
	{
		sprintf(s, "%d", tile->units);

		ft_sdl_text_blit(ren, data->font, s, tile->pos.x*50+50/2, tile->pos.y*50+50/2,
							ALIGN_CENTER, ALIGN_CENTER, 0, 0, 0);
	}
}


