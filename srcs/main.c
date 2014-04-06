/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:07
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 12:34:31
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
	t_img img;
	t_game game;
	int quit = 0;
	t_tile_type map[NB_TILE_Y][NB_TILE_X];
	unsigned int timer = 0;

	(void)argc, (void)argv;
	ft_sdl_init(&sdl);
	ft_sdl_img_all_load(&sdl, &img);	

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
		ft_map_blit(map, sdl.ren, &img);
		ft_map_hover_blit(sdl.ren, &game);

			
		// flip
		SDL_RenderPresent(sdl.ren);

		if (SDL_GetTicks() < timer + 1000/FPS)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-timer));
	}

	IMG_Quit();

	SDL_DestroyTexture(img.green);
	SDL_DestroyTexture(img.blue);
	SDL_DestroyTexture(img.brown);
	SDL_DestroyRenderer(sdl.ren);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();

	return 0;
}

