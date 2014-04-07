/* 
* @Author: Adrien Chardon
* @Date:   2014-04-06 21:55:18
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-07 14:30:15
*/

#ifndef FT_IA_H
#define FT_IA_H

#include "constantes.h"
#include "ft_tile.h"

void ft_ia_play(t_game *game, t_player player);
t_dir ft_ia_closer_town_get(t_game *game, int x, int y);

#endif /* FT_IA_H */
