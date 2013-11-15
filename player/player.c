#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define MAX_X 100
#define MAX_Y 25

char map[MAX_Y][MAX_X];

#include "dummy.h"

int main()
{
	int i = 1;
	//printf("Enter player number - 1 or 2?\n");
	//scanf("%d",&i);

	key_t data_shm_key = 4567;
	key_t server_sem_key = 5678;
	key_t player_sem_key = 7890;
	key_t map_shm_key = 6789;

	void *data_shm_addr = NULL;
	int data_shm_size = sizeof(int) * 4;
	int data_shm_id = shmget(data_shm_key+i-1, data_shm_size, 0666);
	int* player_data = (int*)shmat(data_shm_id, data_shm_addr, 0);

	void *map_shm_addr = NULL;
	int map_shm_size = sizeof(char) * MAX_X * MAX_Y;
	int map_shm_id = shmget(map_shm_key+i-1, map_shm_size, 0666);
	char* player_map = (char*)shmat(map_shm_id, map_shm_addr, 0);

	int server_sem_id = semget(server_sem_key+i-1, 1, IPC_CREAT | 0666);

	int player_sem_id = semget(player_sem_key+i-1, 1, IPC_CREAT | 0666);

	struct sembuf sem_down;
	sem_down.sem_num = 0;
	sem_down.sem_op = -1;
	sem_down.sem_flg = 0;

	struct sembuf sem_up;
	sem_up.sem_num = 0;
	sem_up.sem_op = 1;
	sem_up.sem_flg = 0;

	semop(player_sem_id, &sem_up, 1);
	semop(server_sem_id, &sem_down, 1);

	while(player_data[3] == 0) {
		memcpy(map, player_map, MAX_Y * MAX_X * sizeof(char));
		do_next_step( player_data[0], player_data[1], &player_data[2] );
		//semop(player_sem_id, &sem_up, 1);
		semop(server_sem_id, &sem_down, 1);
	}

	semop(player_sem_id, &sem_up, 1);

	return 0;
}
