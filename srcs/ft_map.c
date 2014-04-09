/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:47:09
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-09 21:57:36
*/


#include "ft_map.h"

void ft_map_init(t_tile map[NB_TILE_Y][NB_TILE_X])
{
	int i, j;

	for (j = 0; j < NB_TILE_Y; ++j)
	{
		for (i = 0; i < NB_TILE_X; ++i)
		{
			if (rand()%100 < 20)
				ft_map_tile_random_init(map, i, j, TILE_TOWN, true);
			else if (rand()%100 < 10)
				ft_map_tile_random_init(map, i, j, TILE_SEA, true);
			else
				ft_map_tile_random_init(map, i, j, TILE_LAND, true);
		}
	}

	ft_map_tile_player_init(map, 2, 2, OWNER_PLAYER_1);
	ft_map_tile_player_init(map, 13, 2, OWNER_PLAYER_2);
	ft_map_tile_player_init(map, 13, 9, OWNER_PLAYER_3);
	ft_map_tile_player_init(map, 2, 9, OWNER_PLAYER_4);
}

void ft_map_tile_random_init(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_tile_type type, int once)
{
	int randomFactor = 30;

	if (ft_tile_is_on_map(x, y) && once)
	{
		/* init */
		map[y][x].pos.x = x;
		map[y][x].pos.y = y;
		map[y][x].owner = OWNER_NONE;
		map[y][x].units = 0;
		map[y][x].lastMove = -1;

		if (type != TILE_TOWN
			|| (type == TILE_TOWN && !ft_tile_is_in_surroundings(map, x, y, TILE_TOWN)))
			map[y][x].type = type;
		else
			map[y][x].type = TILE_LAND;

		// recurs if sea - for creating oceans
		if (type == TILE_SEA)
		{
			if (rand()%100 < randomFactor)
				ft_map_tile_random_init(map, x, y-1, type, false);
			if (rand()%100 < randomFactor)
				ft_map_tile_random_init(map, x, y+1, type, false);
			if (rand()%100 < randomFactor)
				ft_map_tile_random_init(map, x-1, y, type, false);
			if (rand()%100 < randomFactor)
				ft_map_tile_random_init(map, x+1, y, type, false);
		}
	}
}

void ft_map_tile_player_init(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_player player)
{
	map[y][x].type = TILE_CAPITAL;
	map[y][x].owner = player;
	map[y][x].units = 20;
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



