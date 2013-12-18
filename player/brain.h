#include <stdlib.h>

/*
 * Available values:
 * MAX_X, MAX_Y - map demensions
 * char map[i][j] - map itself
 *
 * Map options:
 * '.' - clear space, available for move
 * '#' - wall, not available for move
 * '*' - treasure, available for move, gives bonus
 * '@' - monster, available for move, gives penalty
 * '0' to '9' - players, available for move
 */

/*
 * Command values:
 * 1 - move left	(cur_x--)
 * 2 - move up		(cur_y++)	- be aware, UP from map point of view is DOWN on the screen
 * 3 - move right	(cur_x++)
 * 4 - move down	(cur_y--)	- be aware, DOWN from map point of view is UP on the screen
 * any other value - do nothing
 */
void do_next_step(int cur_x, int cur_y, int *command)
{
	int res = rand() % 5;
	// Some logick here
	*command = res;
};
