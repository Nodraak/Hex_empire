/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:03:01
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-10 12:12:50
*/


#include "ft_sdl.h"

void ft_sdl_init(t_sdl *sdl)
{
	/* SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error SDL_Init() in file %s line %d : %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	Uint32 flag = 0;//SDL_WINDOW_FULLSCREEN;
	SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, flag, &sdl->win, &sdl->ren);
	if (sdl->win == NULL || sdl->ren == NULL)
	{
		fprintf(stderr, "Error SDL_CreateWindow() in file %s line %d : %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_SetWindowTitle(sdl->win, "Squared Empire - Nodraak");

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	//SDL_RenderSetLogicalSize(sdl->ren, SCREEN_W, SCREEN_H);

	/* SDL IMAGE */
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		fprintf(stderr, "Error IMG_Init() in file %s line %d : %s\n", __FILE__, __LINE__, IMG_GetError());
		exit(EXIT_FAILURE);
	}

	/* SDL TTF */
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Error TTF_Init() in file %s line %d : %s\n", __FILE__, __LINE__, TTF_GetError());
		exit(EXIT_FAILURE);
	}





	sdl->winRect.w = SCREEN_W;
	sdl->winRect.h = SCREEN_H;
	sdl->winRect.x = 0;
	sdl->winRect.y = 0;
}


SDL_Texture *ft_sdl_tex_load(char *path, SDL_Renderer *ren, int numClockwiseTurns)
{
	SDL_Surface *ptr = NULL;
	SDL_Texture *tex = NULL;

	ptr = IMG_Load(path);
	if (ptr == NULL)
	{
		fprintf(stderr, "Error IMG_Load() for file %s in file %s line %d : %s\n", path, __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (numClockwiseTurns)
	{
		ptr = rotateSurface90Degrees(ptr, numClockwiseTurns);
		if (ptr == NULL)
		{
			fprintf(stderr, "Error IMG_Load() for file %s in file %s line %d : %s\n", path, __FILE__, __LINE__, SDL_GetError());
			exit(EXIT_FAILURE);
		}
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

void ft_sdl_data_load(t_sdl *sdl, t_data *data)
{
	data->tile[TILE_LAND] = ft_sdl_tex_load("data/land.png", sdl->ren, 0);
	data->tile[TILE_SEA] = ft_sdl_tex_load("data/sea.png", sdl->ren, 0);
	data->tile[TILE_TOWN] = ft_sdl_tex_load("data/town.png", sdl->ren, 0);
	data->tile[TILE_CAPITAL] = ft_sdl_tex_load("data/capital.png", sdl->ren, 0);

	int i;
	for (i = 0; i < DIR_LAST; ++i)
		data->edge[i] = ft_sdl_tex_load("data/edge.png", sdl->ren, i);

	data->hover = ft_sdl_tex_load("data/hover.png", sdl->ren, 0);
	data->enabled = ft_sdl_tex_load("data/hover2.png", sdl->ren, 0);
	
	data->font = TTF_OpenFont("data/Furmanite.ttf", 20);
 	if (data->font == NULL)
 	{
		fprintf(stderr, "Error TTF_OpenFont() in file %s line %d : %s\n", __FILE__, __LINE__, TTF_GetError());
		exit(EXIT_FAILURE);
	}
}

void ft_sdl_texture_blit(SDL_Renderer *ren, SDL_Texture *tex, int x, int y)
{
	int w, h;
	SDL_Rect rect;

	if (SDL_QueryTexture(tex, NULL, NULL, &w, &h) != 0)
	{
		fprintf(stderr, "Error SDL_QueryTexture() in file %s line %d : %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;

	SDL_RenderCopy(ren, tex, NULL, &rect);
}


void ft_sdl_text_blit(SDL_Renderer *ren, TTF_Font *font, char *text, int x, int y,
						int alignX, int alignY, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color color = {r, g, b, 0};
	SDL_Surface *surface = NULL;
	SDL_Texture *tex = NULL;

	surface = TTF_RenderText_Solid(font, text, color);
	tex = SDL_CreateTextureFromSurface(ren, surface);

	if (alignX == ALIGN_CENTER)
		x -= surface->w/2;
	if (alignY == ALIGN_CENTER)
		y -= surface->h/2;

	ft_sdl_texture_blit(ren, tex, x, y);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(tex);
}

