/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 17:50:08
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-05 19:09:45
*/

#ifndef	MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constantes.h"
#include "ft_sdl.h"

void ft_map_init(t_tile_type map[NB_TILE_Y][NB_TILE_X]);
void ft_map_blit(t_tile_type map[NB_TILE_Y][NB_TILE_X], SDL_Renderer *ren, t_img *img);
void ft_map_hover_blit(SDL_Renderer *ren, t_game *game);


#endif /* MAP_H */
