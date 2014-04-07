/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 19:52:03
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-07 13:37:24
*/

#include "ft_game.h"

void ft_game_init(t_game *game)
{
	game->mouse.x = 0;
	game->mouse.y = 0;

	game->selected.x = 0;
	game->selected.y = 0;
	game->isATileSelected = 0;

	game->turn = 0;
	game->currentPlayerMovesLeft = 5;

	game->quitGame = 0;
}

void ft_game_draw(t_sdl *sdl, t_data *data, t_game *game)
{
	// clear rederer
	SDL_SetRenderDrawColor(sdl->ren, 0, 0, 0, 255); // black + opaque
	SDL_RenderClear(sdl->ren);
	// draw background
	SDL_SetRenderDrawColor(sdl->ren, 128, 128, 128, 0);
	SDL_RenderFillRect(sdl->ren, &sdl->winRect);
	// draw tiles
	ft_map_blit(game->map, sdl, data);
	ft_map_hover_blit(sdl->ren, data->mask, game);
	// draw stuff : movess left
	char s[1024];
	sprintf(s, "%c Turn : %d", 123, game->turn);
	ft_sdl_text_blit(sdl->ren, data->font, s, 825, 50, ALIGN_NONE, ALIGN_NONE, 0, 0, 0);
	sprintf(s, "Moves left : %d", game->currentPlayerMovesLeft);
	ft_sdl_text_blit(sdl->ren, data->font, s, 825, 75, ALIGN_NONE, ALIGN_NONE, 0, 0, 0);

	// flip screen
	SDL_RenderPresent(sdl->ren);
}

void ft_game_global_turn_end(t_game *game)
{
	// end human player turn
	ft_game_player_turn_end(game, OWNER_PLAYER_1);

	t_player i;
	for (i = OWNER_PLAYER_2; i < OWNER_PLAYER_LAST; ++i)
	{
		game->currentPlayerMovesLeft = 5;
		ft_ia_play(game, i);
		ft_game_player_turn_end(game, i);
	}

	game->turn++;
	game->currentPlayerMovesLeft = 5;
}

void ft_game_player_turn_end(t_game *game, t_player player)
{
	int i, j;
	int nbTilesOwned = 0, nbTownsOwned = 0;
	int bonus = 0;

	// count nb tiles and towns owned by the player
	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].owner == player)
			{
				nbTilesOwned ++;
				if (game->map[j][i].type == TILE_TOWN || game->map[j][i].type == TILE_CAPITAL)
					nbTownsOwned ++;
			}
		}
	}

	if (nbTownsOwned != 0)
		bonus = (nbTilesOwned/5) / nbTownsOwned; // 1 bonus unit each 5 tiles owned

	for (i = 0; i < NB_TILE_X; ++i)
	{
		for (j = 0; j < NB_TILE_Y; ++j)
		{
			if (game->map[j][i].owner == player)
			{
				if (game->map[j][i].type == TILE_TOWN)
					game->map[j][i].units += 5 + bonus;
				if (game->map[j][i].type == TILE_CAPITAL)
					game->map[j][i].units += 10 + bonus;

				if (game->map[j][i].units > 99)
					game->map[j][i].units = 99;
			}
		}
	}
}




