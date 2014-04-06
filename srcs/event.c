/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 12:32:14
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 15:01:11
*/

#include "event.h"

void ft_event_update(int *quit, t_game *game)
{
	SDL_Event e;
	
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				*quit = 1;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						*quit = 1;
						break;

					default:
						//printf("default : %c\n", e.key.keysym.sym);
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				game->mouse.x = e.motion.x;
				game->mouse.y = e.motion.y;
				break;

			case SDL_MOUSEBUTTONUP:
				ft_tile_selected_update(game);
				break;

			default:
				//printf("unhandled\n");
				break;
		}
	}
}

