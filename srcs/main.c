/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:07
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 22:51:17
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "ft_sdl.h"
#include "ft_map.h"
#include "ft_tile.h"
#include "ft_event.h"
#include "ft_game.h"
#include "ft_ia.h"

#include <time.h>

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

	srand(42);

	while (!game.quitGame)
	{
		timer = SDL_GetTicks();

		/***********
		 *  EVENT  *
		 ***********/
		ft_event_update(&game);

		// next turn
		if (game.currentPlayerMovesLeft <= 0)
		{
			// end human player turn
			ft_game_player_turn_end(&game, OWNER_PLAYER_1);
			// ia 1 = player 2 plays
			game.currentPlayerMovesLeft = 5;
			ft_ia_play(&game, OWNER_PLAYER_2);
			ft_game_player_turn_end(&game, OWNER_PLAYER_2);
			// ia 2 = player 3 plays
			game.currentPlayerMovesLeft = 5;
			ft_ia_play(&game, OWNER_PLAYER_3);
			ft_game_player_turn_end(&game, OWNER_PLAYER_3);
			// ia 3 = player 4 plays
			game.currentPlayerMovesLeft = 5;
			ft_ia_play(&game, OWNER_PLAYER_4);
			ft_game_player_turn_end(&game, OWNER_PLAYER_4);

			game.turn++;
			game.currentPlayerMovesLeft = 5;
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

