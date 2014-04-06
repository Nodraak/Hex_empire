/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 20:36:23
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 20:40:26
*/

#ifndef FT_GAME_H
#define FT_GAME_H

#include "constantes.h"
#include "ft_map.h"

void ft_game_init(t_game *game);
void ft_game_draw(t_sdl *sdl, t_data *data, t_game *game);
void ft_game_player_turn_end(t_game *game, t_player player);


#endif /* FT_GAME_H */
