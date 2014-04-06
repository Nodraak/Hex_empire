/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:47:09
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 18:17:26
*/


#include "ft_map.h"

void ft_map_init(t_tile map[NB_TILE_Y][NB_TILE_X])
{
	int i, j;
	t_tile_type last = TILE_LAND;

	for (j = 0; j < NB_TILE_Y; ++j)
	{
		for (i = 0; i < NB_TILE_X; ++i)
		{
			/* type */
			int random = rand()%100;

			if (random >= 0 && random < 75)
				;
			else if (random >= 75 && random < 95)
				last = TILE_LAND;
			else if (random >= 95 && random < 100)
				last = TILE_SEA;

			if (random < 10)
				map[j][i].type = TILE_TOWN;
			else	
				map[j][i].type = last;

			/* pos */
			map[j][i].pos.x = i;
			map[j][i].pos.y = j;

			/* owner */
			map[j][i].owner = OWNER_NONE;

			/* units */
			map[j][i].units = 0;

		}
	}

	map[1][1].type = TILE_CAPITAL;
	map[1][1].owner = OWNER_PLAYER_1;
	map[1][1].units = 20;

	map[5][5].type = TILE_CAPITAL;
	map[5][5].owner = OWNER_PLAYER_2;
	map[5][5].units = 20;

}

void ft_map_blit(t_tile map[NB_TILE_Y][NB_TILE_X], t_sdl *sdl, t_data *data)
{
	int i, j;

	for (j = 0; j < NB_TILE_Y; ++j)
	{
		for (i = 0; i < NB_TILE_X; ++i)
		{
			ft_tile_blit(sdl->ren, data, &map[j][i]);
		}
	}
}


void ft_map_hover_blit(SDL_Renderer *ren, t_game *game)
{
	SDL_Rect rect;

	if (game->mouse.x < 800)
	{
		rect.x = game->mouse.x/50*50;
		rect.y = game->mouse.y/50*50;
		rect.w = 50;
		rect.h = 50;

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderDrawRect(ren, &rect);
	}

	if (game->isATileSelected)
	{
		rect.x = game->selected.x*50;
		rect.y = game->selected.y*50;
		rect.w = 50;
		rect.h = 50;

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderDrawRect(ren, &rect);
	}
}



