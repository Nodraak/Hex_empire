/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 18:40:55
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
			if (ft_tile_move(&game->map[game->selected.y][game->selected.x],
							&game->map[game->mouse.y/50][game->mouse.x/50]))
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


int ft_tile_move(t_tile *old, t_tile *new)
{
	// conquer new land or move unit
	if (new->owner == OWNER_NONE || new->owner == OWNER_PLAYER_1)
	{
		new->owner = OWNER_PLAYER_1;
		new->units += old->units;
	
		old->units = 0;

		return 1;
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
		}
		// attack lost
		else
		{
			new->units -= old->units;

			old->units = 0;
		}

		return 1;
	}
	else
		printf("dont know what to do 1\n");

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


