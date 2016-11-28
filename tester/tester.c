#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "map_4.h"
#include "brain.c"

#define NUM_OF_MONSTERS 10
#define NUM_OF_TREASURES 10
#define PLAYERS 1
#define STEPS 1000000

int continue_game(int step) {

	if(step > STEPS)
		return 0;

	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++)
			if (clear_map[y][x] == '*')
				return 1;

	return 0;
};


struct monster {
	int x;
	int y;
	int alive;
};

monster monsters[NUM_OF_MONSTERS];

int* player_data[PLAYERS];
int scores[PLAYERS];

void check_killed_monsters(int x, int y)
{
	for(int i = 0; i < NUM_OF_MONSTERS; i++)
		if( (monsters[i].x == x) && (monsters[i].y == y) )
			monsters[i].alive = 0;
};

void check_attacked_players(int num)
{
	for( int i = 0; i < PLAYERS; i++) {
		if( (player_data[i][0] == monsters[num].x) && (player_data[i][1] == monsters[num].y) ) {
			scores[i] -= 1000;
			monsters[num].alive = 0;
		}
	}
};

void process_monster_move(int num, int next_move)
{
	int next_x = monsters[num].x;
	int next_y = monsters[num].y;

	if(next_move == 1)
		next_x--;
	else if(next_move == 2)
		next_y++;
	else if(next_move == 3)
		next_x++;
	else if(next_move == 4)
		next_y--;
	else
		return;

	if( (map[next_y][next_x] == '#') || (map[next_y][next_x] == '*') ) {
		return;
	} else {
		monsters[num].x = next_x;
		monsters[num].y = next_y;
	}
	return;
};

void move_monsters()
{
	for(int i = 0; i < NUM_OF_MONSTERS; i++)
		if( monsters[i].alive == 1 ) {
			process_monster_move(i, rand() % 5);
			check_attacked_players(i);
		}
};

void get_random_place(int* x, int* y)
{
	int cur_x = rand() % MAX_X;
	int cur_y = rand() % MAX_Y;
	while( clear_map[cur_y][cur_x] != '.' ) {
		cur_x = rand() % MAX_X;
		cur_y = rand() % MAX_Y;
	}
	*x = cur_x;
	*y = cur_y;
};

void init_monsters()
{
	for(int i = 0; i < NUM_OF_MONSTERS; i++) {
		monsters[i].alive = 1;
		get_random_place(&monsters[i].x, &monsters[i].y);
	}
};

void init_treasures()
{
	int x;
	int y;
	for(int i = 0; i < NUM_OF_TREASURES; i++) {
		get_random_place(&x, &y);
		clear_map[y][x] = '*';
	}
};

void print_map(int* player_data[], int num)
{
	char local_map[MAX_Y][MAX_X];
	memcpy(local_map, map, MAX_Y * MAX_X * sizeof(char));

	for( int i = 0; i < num; i++)
		local_map[ player_data[i][1] ][ player_data[i][0] ] = '0' + i;

	write(1,"\E[H\E[2J",7);

	for(int i = 0; i < MAX_Y; i++) {
		for(int j = 0; j < MAX_X; j++)
			if(local_map[i][j] == '.')
				printf("\033[30m%c\033[0m", local_map[i][j]);
			else if (local_map[i][j] == '#')
				printf("\033[32m%c\033[0m", local_map[i][j]);
			else if(local_map[i][j] == '*')
				printf("\033[34m%c\033[0m", local_map[i][j]);
			else if(local_map[i][j] == '@')
				printf("\033[31m%c\033[0m", local_map[i][j]);
			else
				printf("\033[104m%c\033[0m", local_map[i][j]);
		printf("\n");
	}
};

int process_next_move(int *player_x, int *player_y, int next_move)
{
	int next_x = *player_x;
	int next_y = *player_y;

	if(next_move == 1)
		next_x--;
	else if(next_move == 2)
		next_y++;
	else if(next_move == 3)
		next_x++;
	else if(next_move == 4)
		next_y--;
	else
		return 0;

	if(map[next_y][next_x] == '#') {
		return 0;
	} else {
		*player_x = next_x;
		*player_y = next_y;
	}

	if(map[next_y][next_x] == '*') {
		map[next_y][next_x] = '.';
		clear_map[next_y][next_x] = '.';
		return 1000;
	}

	if(map[next_y][next_x] == '@') {
		map[next_y][next_x] = '.';
		clear_map[next_y][next_x] = '.';
		check_killed_monsters(next_x, next_y);
		return -1000;
	}

	return 0;
};

void update_player_map()
{
	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++)
			map[y][x] = clear_map[y][x];
	for(int i = 0; i < NUM_OF_MONSTERS; i++)
		if( monsters[i].alive == 1 )
			map[monsters[i].y][monsters[i].x] = '@';

};

void update_main_map()
{
	memcpy(map, clear_map, MAX_Y * MAX_X * sizeof(char));
	for(int i = 0; i < NUM_OF_MONSTERS; i++)
		if( monsters[i].alive == 1 )
			map[monsters[i].y][monsters[i].x] = '@';
};

int main()
{
	srand(time(NULL)) ;

	for( int i = 0; i < PLAYERS; i++) 
		player_data[i] = (int*)malloc(4*sizeof(int));

	// player_x && player_y
	for( int i = 0; i < PLAYERS; i++) 
		get_random_place(&player_data[i][0], &player_data[i][1]);

	for( int i = 0; i < PLAYERS; i++) {
		// Next move undefined
		player_data[i][2] = -1;
		// Game online
		player_data[i][3] = 0;
		scores[i] = 0;
		update_player_map();
	}

	int step = 0;

	init_monsters();

	init_treasures();
	update_main_map();
	print_map(player_data, PLAYERS);

	while( continue_game(step) == 1 ) {

		move_monsters();
		update_main_map();

		print_map(player_data, PLAYERS);
		for( int i = 0; i < PLAYERS; i++) {
			do_next_step( player_data[i][0], player_data[i][1], &player_data[i][2] );
			if( player_data[i][2] != -1 ) {
				scores[i] += process_next_move(&player_data[i][0], &player_data[i][1], player_data[i][2]);
				update_player_map();
				player_data[i][2] = -1;
			}
		}

		printf("Step %d\n", step);
		for( int i = 0; i < PLAYERS; i++)
			printf("Player %d. Scores: %d\n", i, scores[i]);

		step++;
		sleep(1);
	}

	return 0;
}
