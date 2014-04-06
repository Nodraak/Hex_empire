/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:50:08
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 14:26:22
*/

#ifndef	MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constantes.h"
#include "ft_sdl.h"

void ft_map_init(t_tile map[NB_TILE_Y][NB_TILE_X]);
void ft_map_blit(t_tile map[NB_TILE_Y][NB_TILE_X], t_sdl *sdl, t_data *data);
void ft_map_units_blit(TTF_Font *font, SDL_Renderer *ren, t_tile *tile);
void ft_map_hover_blit(SDL_Renderer *ren, t_game *game);


#endif /* MAP_H */
