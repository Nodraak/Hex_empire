/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:47:09
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 12:34:31
*/


#include "map.h"

void ft_map_init(t_tile_type map[NB_TILE_Y][NB_TILE_X])
{
	int i, j;
	t_tile_type last = E_TILE_GREEN;

	for (j = 0; j < NB_TILE_Y; ++j)
	{
		for (i = 0; i < NB_TILE_X; ++i)
		{
			int random = rand()%100;

			if (random >= 0 && random < 75)
				;
			else if (random >= 75 && random < 95)
				last = E_TILE_GREEN;
			else if (random >= 95 && random < 100)
				last = E_TILE_BLUE;
			else
				printf("caca\n");

			if (random < 10)
				map[j][i] = E_TILE_BROWN;
			else	
				map[j][i] = last;
		}
	}
}

void ft_map_blit(t_tile_type map[NB_TILE_Y][NB_TILE_X], SDL_Renderer *ren, t_img *img)
{
	int i, j;

	for (j = 0; j < NB_TILE_Y; ++j)
	{
		for (i = 0; i < NB_TILE_X; ++i)
		{
			int x = i * 50;
			int y = j * 50;

			switch (map[j][i])
			{
				case E_TILE_BLUE:
					ft_sdl_texture_draw(ren, img->blue, x, y);
					break;
				case E_TILE_BROWN:
					ft_sdl_texture_draw(ren, img->brown, x, y);
					break;
				case E_TILE_GREEN:
					ft_sdl_texture_draw(ren, img->green, x, y);
					break;
			}
		}
	}
}

void ft_map_hover_blit(SDL_Renderer *ren, t_game *game)
{
	SDL_Rect rect;
	rect.x = game->mouse.x*50;
	rect.y = game->mouse.y*50;
	rect.w = 50;
	rect.h = 50;


	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderDrawRect(ren, &rect);

}



