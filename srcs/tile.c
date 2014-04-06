/* 
* @Author: Adrien Chardon
* @Date:   2014-04-05 18:35:55
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-04-06 15:01:11
*/

#include "tile.h"


void ft_tile_selected_update(t_game *game)
{
	if (game->selected.x == game->mouse.x/50 && game->selected.y == game->mouse.y/50
		&& game->isATileSelected == 1)
	{
		game->isATileSelected = 0;
	}
	else
	{
		game->selected.x = game->mouse.x/50;
		game->selected.y = game->mouse.y/50;

		game->isATileSelected = 1;
	}
}



