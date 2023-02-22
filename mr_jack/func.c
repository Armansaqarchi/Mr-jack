#include <stdio.h>
#include <stdlib.h>

typedef struct room {
	int type;
	int activity;
	char name[3];
	int visiblity;
	int visiblity2;
	int escape;
	int light_num;
	int mr_jack;
}room;



void Map_Creator(room array[9][13]) {
	(array)[0][0].type = 4;
	(array)[0][1].type = 4;
	(array)[0][2].type = 4;
	(array)[0][3].type = 4;
	(array)[0][4].type = 4;
	(array)[0][5].type = 3;
	(array)[0][6].type = 4;
	(array)[0][7].type = 4;
	(array)[0][8].type = 4;
	(array)[0][9].type = 4;
	(array)[0][10].type = 4;
	(array)[0][11].type = 4;
	(array)[0][12].type = 4;
	(array)[1][0].type = 4;
	(array)[1][1].type = 0;
	(array)[1][2].type = 4;
	(array)[1][3].type = 1;
	(array)[1][4].type = 0;
	(array)[1][5].type = 2;
	(array)[1][6].type = 0;
	(array)[1][7].type = 0;
	(array)[1][8].type = 4;
	(array)[1][9].type = 4;
	(array)[1][10].type = 4;
	(array)[1][11].type = 3;
	(array)[1][12].type = 4;
	(array)[2][0].type = 4;
	(array)[2][1].type = 0;
	(array)[2][2].type = 2;
	(array)[2][3].type = 0;
	(array)[2][4].type = 0;
	(array)[2][5].type = 1;
	(array)[2][6].type = 0;
	(array)[2][7].type = 1;
	(array)[2][8].type = 0;
	(array)[2][9].type = 0;
	(array)[2][10].type = 0;
	(array)[2][11].type = 2;
	(array)[2][12].type = 0;
	(array)[3][0].type = 3;
	(array)[3][1].type = 1;
	(array)[3][2].type = 0;
	(array)[3][3].type = 1;
	(array)[3][4].type = 0;
	(array)[3][5].type = 3;
	(array)[3][6].type = 0;
	(array)[3][7].type = 2;
	(array)[3][8].type = 0;
	(array)[3][9].type = 1;
	(array)[3][10].type = 0;
	(array)[3][11].type = 0;
	(array)[3][12].type = 0;
	(array)[4][0].type = 0;
	(array)[4][1].type = 1;
	(array)[4][2].type = 1;
	(array)[4][3].type = 0;
	(array)[4][4].type = 0;
	(array)[4][5].type = 1;
	(array)[4][6].type = 0;
	(array)[4][7].type = 1;
	(array)[4][8].type = 0;
	(array)[4][9].type = 0;
	(array)[4][10].type = 0;
	(array)[4][11].type = 1;
	(array)[4][12].type = 0;
	(array)[5][0].type = 0;
	(array)[5][1].type = 0;
	(array)[5][2].type = 0;
	(array)[5][3].type = 1;
	(array)[5][4].type = 0;
	(array)[5][5].type = 2;
	(array)[5][6].type = 0;
	(array)[5][7].type = 3;
	(array)[5][8].type = 0;
	(array)[5][9].type = 1;
	(array)[5][10].type = 1;
	(array)[5][11].type = 1;
	(array)[5][12].type = 3;
	(array)[6][0].type = 0;
	(array)[6][1].type = 2;
	(array)[6][2].type = 0;
	(array)[6][3].type = 0;
	(array)[6][4].type = 0;
	(array)[6][5].type = 1;
	(array)[6][6].type = 0;
	(array)[6][7].type = 1;
	(array)[6][8].type = 0;
	(array)[6][9].type = 0;
	(array)[6][10].type = 0;
	(array)[6][11].type = 0;
	(array)[6][12].type = 0;
	(array)[7][0].type = 0;
	(array)[7][1].type = 0;
	(array)[7][2].type = 3;
	(array)[7][3].type = 4;
	(array)[7][4].type = 0;
	(array)[7][5].type = 0;
	(array)[7][6].type = 0;
	(array)[7][7].type = 2;
	(array)[7][8].type = 0;
	(array)[7][9].type = 1;
	(array)[7][10].type = 2;
	(array)[7][11].type = 0;
	(array)[7][12].type = 4;
	(array)[8][0].type = 4;
	(array)[8][1].type = 4;
	(array)[8][2].type = 4;
	(array)[8][3].type = 4;
	(array)[8][4].type = 4;
	(array)[8][5].type = 4;
	(array)[8][6].type = 0;
	(array)[8][7].type = 3;
	(array)[8][8].type = 0;
	(array)[8][9].type = 4;
	(array)[8][10].type = 4;
	(array)[8][11].type = 4;
	(array)[8][12].type = 4;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			(array)[i][j].name[0] = 'N';
			(array)[i][j].name[1] = 'O';
			(array)[i][j].name[2] = '\0';
			(array)[i][j].escape = 0;
			(array)[i][j].activity = 1;
			array[i][j].light_num = 0;
			array[i][j].mr_jack = 0;
			array[i][j].visiblity = 0;
		}
	}
	(array)[1][11].escape = 1;
	(array)[7][11].escape = 1;
	(array)[7][1].escape = 1;
	(array)[1][1].escape = 1;
	(array)[4][0].name[0] = 'J';
	(array)[4][0].name[1] = 'W';
	(array)[4][0].name[2] = '\0';
	(array)[5][4].name[0] = 'I';
	(array)[5][4].name[1] = 'L';
	(array)[5][4].name[2] = '\0';
	(array)[6][6].name[0] = 'S';
	(array)[6][6].name[1] = 'H';
	(array)[6][6].name[2] = '\0';
	(array)[8][8].name[0] = 'M';
	(array)[8][8].name[1] = 'S';
	(array)[8][8].name[2] = '\0';
	(array)[4][8].name[0] = 'J';
	(array)[4][8].name[1] = 'B';
	(array)[4][8].name[2] = '\0';
	(array)[3][6].name[0] = 'J';
	(array)[3][6].name[1] = 'S';
	(array)[3][6].name[2] = '\0';
	(array)[4][12].name[0] = 'S';
	(array)[4][12].name[1] = 'G';
	(array)[4][12].name[2] = '\0';
	(array)[1][4].name[0] = 'W';
	(array)[1][4].name[1] = 'G';
	(array)[1][4].name[2] = '\0';
	array[1][11].activity = 0;
	array[7][1].activity = 0;
	array[7][7].activity = 0;
	array[1][5].activity = 0;
	array[1][11].activity = 0;
	array[7][2].activity = 0;
	array[6][1].light_num = 1;
	array[2][11].light_num = 2;
	array[2][2].light_num = 3;
	array[7][10].light_num = 4;


	

}


void visiblity(room array[9][13]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			array[i][j].visiblity = 0;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if ((array)[i][j].type == 2 && (array)[i][j].activity == 1) {
				(array)[i][j].visiblity = 1;
				if (j % 2 == 0) {
					(array)[i][j].visiblity = 1;
					if (j - 1 >= 0) {
						(array)[i][j - 1].visiblity = 1;
					}
					if (j - 1 >= 0 && i - 1 >= 0) {
						(array)[i - 1][j - 1].visiblity = 1;
					}
					if (i - 1 >= 0) {
						(array)[i - 1][j].visiblity = 1;
					}
					if (i + 1 <= 9) {
						(array)[i + 1][j].visiblity = 1;
					}
					if (j + 1 <= 13) {
						(array)[i][j + 1].visiblity = 1;
					}
					if (i - 1 >= 0 && j + 1 <= 13) {
						(array)[i - 1][j + 1].visiblity = 1;
					}

				}
				else {
					if (j - 1 >= 0) {
						(array)[i][j - 1].visiblity = 1;
					}
					if (i + 1 <= 9 && j - 1 >= 0) {
						(array)[i + 1][j - 1].visiblity = 1;
					}
					if (i + 1 <= 9) {
						(array)[i + 1][j].visiblity = 1;
					}
					if (i + 1 <= 9 && j + 1 <= 13) {
						(array)[i + 1][j + 1].visiblity = 1;
					}
					if (i - 1 >= 0) {
						(array)[i - 1][j].visiblity = 1;
					}
					if (j + 1 <= 13) {
						(array)[i][j + 1].visiblity = 1;
					}
				}
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (j % 2 == 1) {
				if (array[i][j].name[0] != 'N') {
					if (array[i][j - 1].name[0] != 'N' && j-1 >= 0) {
						array[i][j].visiblity = 1;
						array[i][j - 1].visiblity = 1;
					}
					if (array[i+1][j-1].name[0] != 'N' && j-1>= 0 && i+1<= 8) {
						array[i][j].visiblity = 1;
						array[i + 1][j - 1].visiblity = 1;
					}
					if (array[i + 1][j].name[0] != 'N' && i+1<= 8) {
						array[i][j].visiblity = 1;
						array[i + 1][j].visiblity = 1;
					}
					if (array[i - 1][j].name[0] != 'N' && i-1 >= 0) {
						array[i][j].visiblity = 1;
						array[i - 1][j].visiblity = 1;
					}
					if (array[i + 1][j + 1].name[0] != 'N' && i+1 <= 8 && j+1 <= 12) {
						array[i][j].visiblity = 1;
						array[i + 1][j + 1].visiblity = 1;
					}
					if (array[i][j + 1].name[0] != 'N' && j+1 <= 12) {
						array[i][j].visiblity = 1;
						array[i][j + 1].visiblity = 1;
					}
				}
			}
			else {
				if (array[i][j].name[0] != 'N') {
					if (array[i-1][j - 1].name[0] != 'N' && j-1 >= 0 && i-1 >= 0) {
						array[i][j].visiblity = 1;
						array[i-1][j - 1].visiblity = 1;
					}
					if (array[i][j - 1].name[0] != 'N' && j-1 >= 0) {
						array[i][j].visiblity = 1;
						array[i][j - 1].visiblity = 1;
					}
					if (array[i-1][j].name[0] != 'N' && i-1 >= 0) {
						array[i][j].visiblity = 1;
						array[i-1][j].visiblity = 1;
					}
					if (array[i + 1][j].name[0] != 'N' && i+1 <= 8) {
						array[i][j].visiblity = 1;
						array[i + 1][j].visiblity = 1;
					}
					if (array[i][j + 1].name[0] != 'N' && j+1 <= 12) {
						array[i][j].visiblity = 1;
						array[i][j + 1].visiblity = 1;
					}
					if (array[i-1][j + 1].name[0] != 'N' && j+1 <= 12 && i-1 >= 0) {
						array[i][j].visiblity = 1;
						array[i-1][j + 1].visiblity = 1;
					}
				}
			}
		}
	}
}

