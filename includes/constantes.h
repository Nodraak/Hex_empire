/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:06:20
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 14:32:10
*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

/*************
 *  INCLUDE  *
 *************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/************
 *  DEFINE  *
 ************/
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

/**********
 *  ENUM  *
 **********/
typedef enum		e_tile_type
{
	TILE_LAND,
	TILE_SEA,
	TILE_TOWN,
	TILE_CAPITAL,
	TILE_LAST
}					t_tile_type;

typedef enum		e_player
{
	OWNER_NONE,
	OWNER_PLAYER_1,
	OWNER_PLAYER_2
}					t_player;

/************
 *  STRUCT  *
 ************/
/* sdl data */
typedef struct 		s_sdl
{
	SDL_Window 		*win;
	SDL_Renderer 	*ren;
	SDL_Rect		winRect;

}					t_sdl;
/* sprites */
typedef struct 		s_data
{
	SDL_Texture		*green;
	SDL_Texture		*blue;
	SDL_Texture		*brown;

	TTF_Font		*font;
}					t_data;
/* simple vector */
typedef struct		s_vector
{
	int x, y;
}					t_vector;
/* game data */
typedef struct		s_game
{
	t_vector		mouse;
	t_vector		selected;
	int				isATileSelected;
}					t_game;
/* tile data */
typedef struct		s_tile
{
	t_vector		pos;
	t_tile_type		type;
	t_player		owner;
	int				units;	// number of units
}					t_tile;



/* notes


SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error report", s, NULL);


*/

#endif /* CONSTANTES_H */
