/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:15
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-05 18:05:33
*/

#ifndef FT_SDL_H
#define FT_SDL_H

/* include */
#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constantes.h"


/* prototypes */
void ft_sdl_init(t_sdl *sdl);
SDL_Texture *ft_sdl_img_one_load(char *path, SDL_Renderer *ren);
void ft_sdl_img_all_load(t_sdl *sdl, t_img *img);

void ft_sdl_texture_draw(SDL_Renderer *ren, SDL_Texture *tex, int x, int y);

#endif /* FT_SDL_H */
