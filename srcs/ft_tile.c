/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 17:48:14
*/

#include "tile.h"


void ft_tile_selected_update(t_game *game)
{
	// unselect
	if (game->selected.x == game->mouse.x/50 && game->selected.y == game->mouse.y/50
		&& game->isATileSelected == 1)
	{
		game->isATileSelected = 0;
	}
	// move
	else if ((game->selected.x != game->mouse.x/50 || game->selected.y != game->mouse.y/50)
		&& game->isATileSelected == 1)
	{
		int dx = game->mouse.x/50 - game->selected.x;
		int dy = game->mouse.y/50 - game->selected.y;

		if (dx*dx + dy*dy <= 2*2)
		{
			ft_tile_move(&game->map[game->selected.y][game->selected.x],
							&game->map[game->mouse.y/50][game->mouse.x/50]);
		}

		game->isATileSelected = 0;
	}
	// select
	else
	{
		game->selected.x = game->mouse.x/50;
		game->selected.y = game->mouse.y/50;

		game->isATileSelected = 1;
	}
}


void ft_tile_move(t_tile *old, t_tile *new)
{
	if (old->owner == OWNER_PLAYER_1)
	{
		// conquer new land or move unit
		if (old->units != 0 && (new->owner == OWNER_NONE || new->owner == OWNER_PLAYER_1))
		{
			new->owner = OWNER_PLAYER_1;
			new->units += old->units;

			old->units = 0;
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
		}
		else
			printf("dont know what to do 1\n");
	}
	// else : you dont own this tile - too bad ...

}

void ft_tile_blit(SDL_Renderer *ren, t_data *data, t_tile *tile)
{
	t_vector blitPos = {tile->pos.x*50, tile->pos.y*50};

	/* tile background */
	switch (tile->type)
	{
		case TILE_SEA:
			ft_sdl_texture_draw(ren, data->blue, blitPos.x, blitPos.y);
			break;
		case TILE_TOWN:
		case TILE_CAPITAL:
			ft_sdl_texture_draw(ren, data->brown, blitPos.x, blitPos.y);
			break;
		case TILE_LAND:
			ft_sdl_texture_draw(ren, data->green, blitPos.x, blitPos.y);
			break;

		default:
			printf("Erreur switch : case not handled. %s %d\n", __FILE__, __LINE__);
			break;
	}

	/* owner */
	if (tile->owner == OWNER_PLAYER_1)
	{
		SDL_SetTextureColorMod(data->mask, 128, 0, 0);
		ft_sdl_texture_draw(ren, data->mask, blitPos.x, blitPos.y);
	}

	/* nb units */
	if (tile->units != 0)
		ft_tile_units_blit(data->font, ren, tile);
}

void ft_tile_units_blit(TTF_Font *font, SDL_Renderer *ren, t_tile *tile)
{
	SDL_Color color = {0, 0, 0, 0};
	SDL_Surface *surface = NULL;
	SDL_Texture *tex = NULL;
	char s[1024];

	sprintf(s, "%d", tile->units);

	surface = TTF_RenderText_Solid(font, s, color);
	tex = SDL_CreateTextureFromSurface(ren, surface);

	ft_sdl_texture_draw(ren, tex, tile->pos.x*50+50/2-surface->w/2, tile->pos.y*50+50/2-surface->h/2);

	SDL_FreeSurface(surface);
}


