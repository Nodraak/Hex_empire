/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:15
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 18:24:54
*/

#ifndef FT_SDL_H
#define FT_SDL_H

/* include */
#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "constantes.h"


/* prototypes */
void ft_sdl_init(t_sdl *sdl);
SDL_Texture *ft_sdl_tex_load(char *path, SDL_Renderer *ren);
void ft_sdl_data_load(t_sdl *sdl, t_data *data);

void ft_sdl_texture_blit(SDL_Renderer *ren, SDL_Texture *tex, int x, int y);
void ft_sdl_text_blit(SDL_Renderer *ren, TTF_Font *font, char *text, int x, int y,
						int alignX, int alignY, Uint8 r, Uint8 g, Uint8 b);

#endif /* FT_SDL_H */
