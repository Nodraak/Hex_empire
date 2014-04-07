/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:47:09
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-07 11:21:52
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

			/* last move */
			map[j][i].lastMove = -1;
		}
	}

	map[2][2].type = TILE_CAPITAL;
	map[2][2].owner = OWNER_PLAYER_1;
	map[2][2].units = 20;

	map[2][14].type = TILE_CAPITAL;
	map[2][14].owner = OWNER_PLAYER_2;
	map[2][14].units = 20;

	map[10][14].type = TILE_CAPITAL;
	map[10][14].owner = OWNER_PLAYER_3;
	map[10][14].units = 20;

	map[10][2].type = TILE_CAPITAL;
	map[10][2].owner = OWNER_PLAYER_4;
	map[10][2].units = 20;

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


void ft_map_hover_blit(SDL_Renderer *ren, SDL_Texture *mask, t_game *game)
{
	if (game->mouse.x < 800)
	{
		SDL_SetTextureColorMod(mask, 64, 64, 64); // gray
		ft_sdl_texture_blit(ren, mask, game->mouse.x/50*50, game->mouse.y/50*50);
	}

	if (game->isATileSelected)
	{
		SDL_SetTextureColorMod(mask, 64, 64, 64); // gray
		ft_sdl_texture_blit(ren, mask, game->selected.x*50, game->selected.y*50);
	}
}



