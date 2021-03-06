/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:36:04
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-10 12:25:07
*/

#ifndef TILE_H
#define TILE_H


#include "constantes.h"
#include "ft_sdl.h"

void ft_tile_selected_update(t_game *game);

int ft_tile_is_able_to_move(t_game *game, int oldX, int oldY, int newX, int newY, t_player player);
int ft_tile_is_able_to_be_annexed(t_game *game, int x, int y);
int ft_tile_is_on_map(int x, int y);

int ft_tile_surroundings_one_try_annexe(t_game *game, int x, int y, t_player player, t_bool simulate);
int ft_tile_surroundings_all_try_annexe(t_game *game, int x, int y, t_player player, t_bool simulate);

int ft_tile_move(t_game *game, int srcx, int srcy, int destx, int desty, t_player player, t_bool simulate);
int ft_tile_score_get(t_tile_type tile);
int ft_tile_is_in_surroundings(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_tile_type tile);

void ft_tile_blit(SDL_Renderer *ren, t_data *data, t_tile *tile);
int ft_tile_need_edge(t_tile map[NB_TILE_Y][NB_TILE_X], int x, int y, t_dir dir);
void ft_tile_owner_blit(SDL_Renderer *ren, t_data *data, t_tile *tile, t_dir dir);

#endif /* TILE_H */
