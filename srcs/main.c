/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:07
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-09 22:00:00
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


Uint8 playerColors[OWNER_PLAYER_LAST][3] = {
	{0, 0, 0},
	{0, 0, 128},
	{128, 0, 0},
	{200, 200, 0},
	{128, 0, 128},
};

char *strDir[DIR_LAST] = {"up", "down", "left", "right", "none"};

char *strTile[TILE_LAST] = {"land", "sea", "town", "capital"};

void ft_cleanup(t_sdl *sdl, t_data *data);
void ft_timer(void);

void ft_cleanup(t_sdl *sdl, t_data *data)
{
	TTF_CloseFont(data->font);
	TTF_Quit();

	IMG_Quit();

	SDL_DestroyTexture(data->green);
	SDL_DestroyTexture(data->blue);
	SDL_DestroyTexture(data->brown);
	SDL_DestroyTexture(data->mask);

	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void ft_timer(void)
{
	static unsigned int timer = 0;

	if (SDL_GetTicks() - timer < 1000/FPS)
	{		
		#ifdef FRAME_DEBUG
			printf("frame ok : %d ms to calc\n", SDL_GetTicks()-timer);
		#endif
	
		SDL_Delay(1000/FPS-(SDL_GetTicks()-timer));
	}
	else
	{
		#ifdef FRAME_DEBUG
			printf("frame is late : %d ms to calcs\n", SDL_GetTicks()-timer);
		#endif
	}

	timer = SDL_GetTicks();
}


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
			ft_game_global_turn_end(&game);

		/**********
		 *  DRAW  *
		 **********/
    	ft_game_draw(&sdl, &data, &game);

		/***************
		 *  FIXED FPS  *
		 ***************/
		ft_timer();
	}

	ft_cleanup(&sdl, &data);

	return 0;
}

