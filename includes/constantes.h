/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:06:20
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 12:35:18
*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

/* include */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* define */
#define SCREEN_W		800
#define SCREEN_H		600
#define FPS				50

#define NB_TILE_X		16
#define NB_TILE_Y		12


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	#define rmask 0xff000000;
	#define gmask 0x00ff0000;
	#define bmask 0x0000ff00;
	#define amask 0x000000ff;
#else
	#define rmask 0x000000ff;
	#define gmask 0x0000ff00;
	#define bmask 0x00ff0000;
	#define amask 0xff000000;
#endif

/* enum */
typedef enum	e_tile_type
{
	E_TILE_GREEN,
	E_TILE_BLUE,
	E_TILE_BROWN
}				t_tile_type;

/* struct */
typedef struct 		s_sdl
{
	SDL_Window 		*win;
	SDL_Renderer 	*ren;
	SDL_Rect		winRect;

}					t_sdl;

typedef struct 		s_img
{
	SDL_Texture		*green;
	SDL_Texture		*blue;
	SDL_Texture		*brown;

}					t_img;

typedef struct		s_vector
{
	int x, y;
}					t_vector;

typedef struct		s_game
{
	t_vector		mouse;
	t_vector		selected;
	int				isATileSelected;
}					t_game;


typedef struct		s_tile
{
	t_vector		pos;
	int				value;
	int				owner;
	int				status; // town, capital, land, sea, ...
}					t_tile;



/* notes


SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error report", s, NULL);


*/

#endif /* CONSTANTES_H */
