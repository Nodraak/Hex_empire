/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 14:06:20
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-10 12:11:37
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
#define SCREEN_W		(800+200)
#define SCREEN_H		600
#define FPS				50

#define NB_TILE_X		16
#define NB_TILE_Y		12

#define t_bool			int
#define false			0
#define true			1

//#define FRAME_DEBUG
//#define PRINT_DEBUG


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
	OWNER_PLAYER_2,
	OWNER_PLAYER_3,
	OWNER_PLAYER_4,
	OWNER_PLAYER_LAST
}					t_player;

typedef enum		e_align
{
	ALIGN_NONE,
	ALIGN_CENTER
}					t_align;

typedef enum		e_dir
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_NONE,
	DIR_LAST
}					t_dir;

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
	SDL_Texture		*tile[TILE_LAST];

	SDL_Texture		*edge[DIR_LAST];
	
	SDL_Texture		*hover;
	SDL_Texture		*enabled;

	TTF_Font		*font;
}					t_data;
/* simple vector */
typedef struct		s_vector
{
	int x, y;
}					t_vector;
/* tile data */
typedef struct		s_tile
{
	t_vector		pos;
	t_tile_type		type;
	t_player		owner;
	int				units;	// number of units
	int				lastMove; // turn when the move occured
}					t_tile;
/* game data */
typedef struct		s_game
{
	t_vector		mouse;

	t_vector		selected;
	int				isATileSelected;
	
	t_tile 			map[NB_TILE_Y][NB_TILE_X];

	int				turn;
	int				currentPlayerMovesLeft;

	int 			quitGame;
}					t_game;

/*  */

extern Uint8 playerColors[OWNER_PLAYER_LAST][3];
extern char *strDir[DIR_LAST];
extern char *strTile[TILE_LAST];

/* notes


SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error report", s, NULL);


*/

#endif /* CONSTANTES_H */
