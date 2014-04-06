/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:07
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 15:34:35
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
	unsigned int timer = 0;

	(void)argc, (void)argv;
	ft_sdl_init(&sdl);
	ft_sdl_data_load(&sdl, &data);
	ft_map_init(game.map);

	game.mouse.x = 0;
	game.mouse.y = 0;
	game.selected.x = 0;
	game.selected.y = 0;
	game.isATileSelected = 0;

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
		ft_map_blit(game.map, &sdl, &data);
		ft_map_hover_blit(sdl.ren, &game);

		// flip
		SDL_RenderPresent(sdl.ren);

		if (SDL_GetTicks() < timer + 1000/FPS)
		{
			SDL_Delay(1000/FPS-(SDL_GetTicks()-timer));
			#ifdef FRAME_DEBUG
				printf("frame ok\n");
			#endif
		}
		else
		{
			#ifdef FRAME_DEBUG
				printf("frame is late\n");
			#endif
		}
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

