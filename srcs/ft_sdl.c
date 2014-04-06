/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:01
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-05 18:22:45
*/


#include "ft_sdl.h"

void ft_sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error SDL_Init() in file %s line %d : %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	
	/*sdl->win = SDL_CreateWindow("Squared empire",
							SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							0, 0,
							SDL_WINDOW_FULLSCREEN_DESKTOP);*/

	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &sdl->win, &sdl->ren);

	if (sdl->win == NULL || sdl->ren == NULL)
	{
		fprintf(stderr, "Error SDL_CreateWindow() in file %s line %d : %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(sdl->ren, SCREEN_W, SCREEN_H);

	/* SDL2 image */
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		fprintf(stderr, "Error IMG_Init() in file %s line %d : %s\n", __FILE__, __LINE__, IMG_GetError());
		exit(EXIT_FAILURE);
	}


	sdl->winRect.w = SCREEN_W;
	sdl->winRect.h = SCREEN_H;
	sdl->winRect.x = 0;
	sdl->winRect.y = 0;
}


SDL_Texture *ft_sdl_img_one_load(char *path, SDL_Renderer *ren)
{
	SDL_Surface *ptr = NULL;
	SDL_Texture *tex = NULL;

	ptr = IMG_Load(path);
	if (ptr == NULL)
	{
		fprintf(stderr, "Error IMG_Load() for file %s in file %s line %d : %s\n", path, __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	tex = SDL_CreateTextureFromSurface(ren, ptr);
	if (tex == NULL)
	{
		fprintf(stderr, "Error SDL_CreateTextureFromSurface() from file %s in file %s line %d : %s\n", path, __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	SDL_FreeSurface(ptr);
	return tex;
}

void ft_sdl_img_all_load(t_sdl *sdl, t_img *img)
{
	img->green = ft_sdl_img_one_load("green.png", sdl->ren);
	img->blue = ft_sdl_img_one_load("blue.png", sdl->ren);
	img->brown = ft_sdl_img_one_load("brown.png", sdl->ren);
}

void ft_sdl_texture_draw(SDL_Renderer *ren, SDL_Texture *tex, int x, int y)
{
	int w, h;
	SDL_Rect rect;

	if (SDL_QueryTexture(tex, NULL, NULL, &w, &h) != 0)
	{
		// error
	}

	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;

	SDL_RenderCopy(ren, tex, NULL, &rect);
}


