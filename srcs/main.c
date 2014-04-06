/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:07
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 20:39:03
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "ft_sdl.h"
#include "ft_map.h"
#include "ft_tile.h"
#include "ft_event.h"
#include "ft_game.h"



int main(int argc, char *argv[])
{
	t_sdl sdl;
	t_data data;
	t_game game;
	unsigned int timer = 0;

	(void)argc, (void)argv;
	ft_sdl_init(&sdl);
	ft_sdl_data_load(&sdl, &data);
	ft_map_init(game.map);
	ft_game_init(&game);

	while (!game.quitGame)
	{
		timer = SDL_GetTicks();

		/***********
		 *  EVENT  *
		 ***********/
		ft_event_update(&game);

		// next turn
		if (game.currentPlayerMovesLeft == 0)
		{
			ft_game_player_turn_end(&game, OWNER_PLAYER_1);
			game.turn++;
			game.currentPlayerMovesLeft = 5;

			// ia plays

		}

		/**********
		 *  DRAW  *
		 **********/
    	ft_game_draw(&sdl, &data, &game);

		/***************
		 *  FIXED FPS  *
		 ***************/
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

