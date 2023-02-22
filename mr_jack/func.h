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


void Map_Creator(room array[9][13]);


void visiblity(room array[9][13]);