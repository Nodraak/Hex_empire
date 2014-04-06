/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:47:09
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 21:50:02
*/


#include "ft_map.h"

void ft_map_init(t_tile map[NB_TILE_Y][NB_TILE_X])
{
	int i, j;

	for (j = 0; j < NB_TILE_Y; ++j)
	{
		for (i = 0; i < NB_TILE_X; ++i)
		{
			/* type */
			map[j][i].type = TILE_LAND;

			if (rand()%100 < 10)
				ft_map_init_tile_type_set(map, i, j, TILE_TOWN);
			if (rand()%100 < 5)
				ft_map_init_tile_type_set(map, i, j, TILE_SEA);

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

void ft_map_init_tile_type_set(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_tile_type tile)
{
	int randomFactor = 30;

	if (x >= 0 && x < NB_TILE_X && y >= 0 && y < NB_TILE_Y
		&& map[y][x].type != tile)
	{
		map[y][x].type = tile;

		// recurs if sea - for creating oceans
		if (tile == TILE_SEA)
		{
			if (rand()%100 < randomFactor)
				ft_map_init_tile_type_set(map, x-1, y, TILE_SEA);
			if (rand()%100 < randomFactor)
				ft_map_init_tile_type_set(map, x+1, y, TILE_SEA);
			if (rand()%100 < randomFactor)
				ft_map_init_tile_type_set(map, x, y-1, TILE_SEA);
			if (rand()%100 < randomFactor)
				ft_map_init_tile_type_set(map, x, y+1, TILE_SEA);

		}
	}
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



