/*
 * Available values:
 * MAX_X, MAX_Y - map demensions
 * char map[y][x] - map itself
 * 
 * Map options:
 * '.' - clear space, available for move
 * '#' - wall, not available for move
 * '*' - treasure, available for move, gives bonus
 * '@' - monster, available for move, gives penalty
 * '0' - player (you)
 */

#define STAY 0
#define LEFT 1
#define RIGHT 3
#define UP 2
#define DOWN 4

/*
 * Command values:
 * 1 - move left (i--)
 * 2 - move up (j++) - it's *down* visually(!)
 * 3 - move right (i++)
 * 4 - move down (j--) - it's *up* visually(!)
 * any other value - do nothing
 */
void do_next_step(int cur_x, int cur_y, int *command);
