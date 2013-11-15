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
 * '1' to '9' - players, available for move
 */

/*
 * Command values:
 * 1 - move left
 * 2 - move up
 * 3 - move right
 * 4 - move down
 * any other value - do nothing
 */
void do_next_step(int cur_x, int cur_y, int *command)
{
	int res = rand() % 5;
	// Some logick here
	*command = res;
};
