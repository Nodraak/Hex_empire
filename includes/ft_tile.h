/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:36:04
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-07 13:22:41
*/

#ifndef TILE_H
#define TILE_H


#include "constantes.h"
#include "ft_sdl.h"

void ft_tile_selected_update(t_game *game);

int ft_tile_is_able_to_move(t_game *game, int oldX, int oldY, int newX, int newY, t_player player);
int ft_tile_is_able_to_be_conquered(t_game *game, int x, int y);
void ft_tile_surroundings_try_conquer(t_game *game, int x, int y, t_player player);

int ft_tile_move(t_tile *old, t_tile *new, t_player player);
int ft_tile_is_in_surroundings(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_tile_type tile);

void ft_tile_blit(SDL_Renderer *ren, t_data *data, t_tile *tile);

#endif /* TILE_H */
