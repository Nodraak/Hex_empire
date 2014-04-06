/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:36:04
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 18:00:13
*/

#ifndef TILE_H
#define TILE_H


#include "constantes.h"
#include "ft_sdl.h"

void ft_tile_selected_update(t_game *game);

void ft_tile_move(t_tile *old, t_tile *new);
void ft_tile_blit(SDL_Renderer *ren, t_data *data, t_tile *tile);
void ft_tile_units_blit(TTF_Font *font, SDL_Renderer *ren, t_tile *tile);


#endif /* TILE_H */
