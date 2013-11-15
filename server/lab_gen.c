#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand( unsigned( time(0)) ) ;

	int MAX_X = 100;
	int MAX_Y = 25;

	char map[MAX_Y][MAX_X];

	printf("#define MAX_X %d\n#define MAX_Y %d\n\nchar map[MAX_Y][MAX_X];\n\nchar clear_map[MAX_Y][MAX_X] = {\n", MAX_X, MAX_Y);

	for(int i = 0; i < MAX_Y; i++)
		for(int j = 0; j < MAX_X; j++)
			map[i][j] = '.';

	for(int i = 0; i < MAX_Y; i++) {
		map[i][MAX_X-1] = '#';
		map[i][0] = '#';
	}

	for(int j = 0; j < MAX_X; j++) {
		map[0][j] = '#';
		map[MAX_Y-1][j] = '#';
	}

	for(int k = 0; k < 100; k++)
	{
		int sx = (rand() % MAX_X);
		int sy = (rand() % MAX_Y);
		int sl = 5 + (rand() % 6);
		int sd = (rand() % 4);

		int dx, dy;
		if(sd == 0) { dx = 1; dy = 0; }
		else if(sd == 1) { dx = 0; dy = 1; }
		else if(sd == 2) { dx = -1; dy = 0; }
		else if(sd == 3) { dx = 0; dy = -1; }
		else { dx = 0; dy = 0; printf("WTF?\n"); }

		for(int i = 0; i < sl; i++)
			if( (sy+dy*i > 0) && (sy+dy*i < MAX_Y-1) && (sx+dx*i > 0) && (sx+dx*i < MAX_X-1) )
				map[sy+dy*i][sx+dx*i] = '#';
	}

	for(int i = 0; i < MAX_Y; i++) {
		for(int j = 0; j < MAX_X; j++) {
			printf("'%c', ", map[i][j]);
		}
		printf("\n");
	}

	printf("};\n");
	return 0;
};
