/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 21:35:09
*/

#include "ft_tile.h"


void ft_tile_selected_update(t_game *game)
{
	/* move if :
		the old and new tiles are !=
		an old tile is selected
		the old tile is owned by the player
		there are units on the old tile
		the player have non zero moves left
		the old tile has not moved yet
	*/
	if ((game->selected.x != game->mouse.x/50 || game->selected.y != game->mouse.y/50)
		&& game->isATileSelected == 1
		&& game->map[game->selected.y][game->selected.x].owner == OWNER_PLAYER_1
		&& game->map[game->selected.y][game->selected.x].units != 0
		&& game->currentPlayerMovesLeft > 0
		&& game->map[game->selected.y][game->selected.x].lastMove < game->turn)
	{
		int dx = game->mouse.x/50 - game->selected.x;
		int dy = game->mouse.y/50 - game->selected.y;

		if (dx*dx + dy*dy <= 2*2)
		{
			int ret = ft_tile_move(&game->map[game->selected.y][game->selected.x],
							&game->map[game->mouse.y/50][game->mouse.x/50]);
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


int ft_tile_move(t_tile *old, t_tile *new)
{
	// conquer new land or move unit
	if (new->owner == OWNER_NONE || new->owner == OWNER_PLAYER_1)
	{
		new->owner = OWNER_PLAYER_1;
		new->units += old->units;
		old->units = 0;

		return 2;
	}
	// attack
	else if (new->owner != OWNER_PLAYER_1 && new->owner != OWNER_NONE)
	{
		// attack win
		if (old->units > new->units)
		{
			new->owner = OWNER_PLAYER_1;
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
		SDL_SetTextureColorMod(data->mask, 128, 0, 0);
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


