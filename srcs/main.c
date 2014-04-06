/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:07
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 14:10:21
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "ft_sdl.h"
#include "map.h"
#include "tile.h"
#include "event.h"


int main(int argc, char *argv[])
{
	t_sdl sdl;
	t_data data;
	t_game game;
	int quit = 0;
	t_tile map[NB_TILE_Y][NB_TILE_X];
	unsigned int timer = 0;

	(void)argc, (void)argv;
	ft_sdl_init(&sdl);
	ft_sdl_data_load(&sdl, &data);
	ft_map_init(map);

	while (!quit)
	{
		timer = SDL_GetTicks();

		ft_event_update(&quit, &game);

    	// clear
		SDL_SetRenderDrawColor(sdl.ren, 0, 0, 0, 255); // black + opaque
		SDL_RenderClear(sdl.ren);
		// bg
		SDL_SetRenderDrawColor(sdl.ren, 128, 128, 128, 0);
		SDL_RenderFillRect(sdl.ren, &sdl.winRect);
		// tile
		ft_map_blit(map, sdl.ren, &data);
		ft_map_hover_blit(sdl.ren, &game);

		/*SDL_Color black = {0, 0, 0, 0};
		SDL_Color white = {255, 255, 255, 0};
		SDL_Surface *surface = TTF_RenderText_Solid(data.font, "42", black);
		SDL_Texture *tex = SDL_CreateTextureFromSurface(sdl.ren, surface);
		ft_sdl_texture_draw(sdl.ren, tex, 110, 110);*/

		// flip
		SDL_RenderPresent(sdl.ren);

		if (SDL_GetTicks() < timer + 1000/FPS)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-timer));
	}

	TTF_CloseFont(data.font);
	TTF_Quit();

	IMG_Quit();

	SDL_DestroyTexture(data.green);
	SDL_DestroyTexture(data.blue);
	SDL_DestroyTexture(data.brown);
	SDL_DestroyRenderer(sdl.ren);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();

	return 0;
}

