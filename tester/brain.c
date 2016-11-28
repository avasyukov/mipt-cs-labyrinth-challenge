#include "player_data.h"

#include <stdlib.h>

void find_nearest_treasure(int cur_x, int cur_y, int* treasure_x, int* treasure_y)
{
	// Init distance with smth really big
	int min_distance = MAX_X + MAX_Y;
	int target_x; 
	int target_y;

	// Scan the map
	for(int y = 0; y < MAX_Y; y++) {
		for(int x = 0; x < MAX_X; x++) {
			// If you see the treasure - ...
			if(map[y][x] == '*') {
				// ... calculate the distance (naive distance measure)
				int dist = abs(cur_y - y) + abs(cur_x - x);
				// If this treasure is closer compared with the previous ones, ...
				if(dist < min_distance) {
					// ... remember coords and update distance
					target_x = x;
					target_y = y;
					min_distance = dist;
				}
			}
		}
	}

	// Return coordinates of the closest treasure
	*treasure_x = target_x;
	*treasure_y = target_y;
};

void do_next_step(int cur_x, int cur_y, int *command)
{
	int res = STAY;
	int target_x, target_y;
	find_nearest_treasure(cur_x, cur_y, &target_x, &target_y);
	printf("My coords: %d %d. Target: %d %d\n", cur_x, cur_y, target_x, target_y);
	if(cur_x > target_x) {
		printf("Move LEFT\n");
		res = LEFT;
	} else if(cur_x < target_x) {
		printf("Move RIGHT\n");
		res = RIGHT;
	} else if(cur_y > target_y) {
		printf("Move DOWN\n");
		res = DOWN;
	} else if(cur_y < target_y) {
		printf("Move UP\n");
		res = UP;
	}
	*command = res;
};
