#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define min(a,b) a>b ? b:a
#define max(a,b) a>b ? a:b



#define WIDTH  1721
#define HEIGHT 757

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

typedef struct characters {
	char name[20];
	struct characters* next;
}characters;

//creating map's rooms
void Map_Creator(room array[9][13]);

void visiblity(room array[9][13]);

int IL_Ability(int i, int j, int i2, int j2, room array[9][13], SDL_Rect* ban, SDL_Rect* ban2, SDL_Rect* ban3, SDL_Rect* ban4, SDL_Rect* final1, SDL_Rect* final2);

void where_is_mr_jack(char first, char second, room array[9][13]);

void delete_node(characters** list, char name[3]);

void visiblity_checker(room array[9][13], char first, char second, SDL_Texture** IL, SDL_Texture** MS, SDL_Texture** SH, SDL_Texture** JW, SDL_Texture** JS, SDL_Texture** JB, SDL_Texture** SG, SDL_Texture** WG, SDL_Texture* IL2, SDL_Texture* MS2, SDL_Texture* SG2, SDL_Texture* JB2, SDL_Texture* JS2, SDL_Texture* JW2, SDL_Texture* WG2, SDL_Texture* SH2);

void movement(room array[9][13], char name[3], SDL_Rect* dest , int * i,int first,int second);

void SH_Ability(characters** list, SDL_Texture** IL_tex, SDL_Texture* IL2_tex, SDL_Texture** MS_tex, SDL_Texture* MS2_tex, SDL_Texture** SH_tex, SDL_Texture* SH2_tex, SDL_Texture** JS_tex, SDL_Texture* JS2_tex, SDL_Texture** JW_tex, SDL_Texture* JW2_tex, SDL_Texture** SG_tex, SDL_Texture* SG2_tex, SDL_Texture** WG_tex, SDL_Texture* WG2_tex, SDL_Texture** JB_tex, SDL_Texture* JB2_tex, char first, char second);

void WG_Ability(SDL_Rect* dest1, SDL_Rect* dest2);

int JB_Ability(int i, int j, int i2, int j2,room array[9][13],SDL_Rect* tmp1, SDL_Rect* tmp2);

void linked_list_shuffle(characters** list,characters** list2,characters** list3);

void MS_Ability(room array[9][13], char name[3], SDL_Rect* dest, int* i, int first, int second);

void etmam(char name[3], room array[9][13], char final[3]);

SDL_Surface* Surface_Creator(char address[200], SDL_Window** win, SDL_Renderer** rend);

SDL_Texture* Texture_Creator(SDL_Renderer** rend, SDL_Surface** surface,SDL_Window* win);




int JS_Ability(int i, int j, int i2, int j2, room array[9][13], SDL_Rect* light1, SDL_Rect* light2, SDL_Rect* light3, SDL_Rect* light4, SDL_Rect* light_1, SDL_Rect* light_2, SDL_Rect* tmp1, SDL_Rect* tmp2, SDL_Rect* tmp3, SDL_Rect* tmp4, SDL_Rect* tmp_1, SDL_Rect* tmp_2);

void text_displayer(char string[500], TTF_Font* font, SDL_Color color, SDL_Renderer* rend);


int main(void){



	SDL_Init(SDL_INIT_EVERYTHING);

	if (TTF_Init() == -1) {
		printf("failed to initialize SDL_TTF due to error : %s\n",SDL_GetError());
	}
	
   //creating window
	SDL_Window* win = SDL_CreateWindow("mr.jack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_RENDERER_ACCELERATED);

	if (win == NULL) {
		printf("cannot create window due to error : %s\n", SDL_GetError());
		return 1;
	}
	//creating renderer
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (rend == NULL) {
		printf("cannot create renderer due to error : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		return 1;
	}
	//int this part we want to load our character's image so we can render it on the screen


	//loading map's image
	SDL_Surface* map = Surface_Creator("D:/6) Programming/mr jack/map/map.PNG",&win,&rend);
	//loading inspector's image
	SDL_Surface* IL = Surface_Creator("D:/6) Programming/mr jack/characters/IL_suspect.PNG",&win,&rend);
	//loading jeremy's image
	SDL_Surface* JB = Surface_Creator("D:/6) Programming/mr jack/characters/JB_suspect.PNG", &win, &rend);
	//loading JS's image 
	SDL_Surface* JS = Surface_Creator("D:/6) Programming/mr jack/characters/JS_suspect.PNG", &win, &rend);
	//loading JW's image
	SDL_Surface* JW = Surface_Creator("D:/6) Programming/mr jack/characters/JW_suspect.PNG", &win, &rend);
	//loading MS's image
	SDL_Surface* MS = Surface_Creator("D:/6) Programming/mr jack/characters/MS_suspect.PNG", &win, &rend);
	//loading SG's image
	SDL_Surface* SG = Surface_Creator("D:/6) Programming/mr jack/characters/SG_suspect.PNG", &win, &rend);
	//loading SH's image
	SDL_Surface* SH = Surface_Creator("D:/6) Programming/mr jack/characters/SH_suspect.PNG", &win, &rend);
	//loading WG's image
	SDL_Surface* WG = Surface_Creator("D:/6) Programming/mr jack/characters/WG_suspect.PNG", &win, &rend);
	//loading inspector's image 2
	SDL_Surface* IL2 = Surface_Creator("D:/6) Programming/mr jack/characters/IL_innocent.PNG", &win, &rend);
	//loading jeremy's image 2
	SDL_Surface* JB2 = Surface_Creator("D:/6) Programming/mr jack/characters/JB_innocent.PNG", &win, &rend);
	//loading JS's image 2
	SDL_Surface* JS2 = Surface_Creator("D:/6) Programming/mr jack/characters/JS_innocent.PNG", &win, &rend);
	//loading JW's image 2
	SDL_Surface* JW2 = Surface_Creator("D:/6) Programming/mr jack/characters/JW_innocent.PNG", &win, &rend);
	//loading MS's image 2
	SDL_Surface* MS2 = Surface_Creator("D:/6) Programming/mr jack/characters/MS_innocent.PNG", &win, &rend);
	//loading SG's image 2
	SDL_Surface* SG2 = Surface_Creator("D:/6) Programming/mr jack/characters/SG_innocent.PNG", &win, &rend);
	//loading SH's image 2
	SDL_Surface* SH2 = Surface_Creator("D:/6) Programming/mr jack/characters/SH_innocent.PNG", &win, &rend);
	//loading WG's image 2
	SDL_Surface* WG2 = Surface_Creator("D:/6) Programming/mr jack/characters/WG_innocent.PNG", &win, &rend);
	//loading bloakcer's image
	SDL_Surface* blocker = Surface_Creator("D:/6) Programming/mr jack/characters/blocker.PNG", &win, &rend);
	//loading ban's image
	SDL_Surface* ban = Surface_Creator("D:/6) Programming/mr jack/characters/ban.PNG", &win, &rend);
	//loading for light1
	SDL_Surface* light1 = Surface_Creator("D:/6) Programming/mr jack/characters/light1.PNG", &win, &rend);
	//loading for light2
	SDL_Surface* light2 = Surface_Creator("D:/6) Programming/mr jack/characters/light2.PNG", &win, &rend);
	//loading for light 3
	SDL_Surface* light3 = Surface_Creator("D:/6) Programming/mr jack/characters/light3.PNG", &win, &rend);
	//loading for light4
	SDL_Surface* light4 = Surface_Creator("D:/6) Programming/mr jack/characters/light4.PNG", &win, &rend);
	//loading for light
	SDL_Surface* light = Surface_Creator("D:/6) Programming/mr jack/characters/light5.PNG", &win, &rend);
	
	

	SDL_Color color = { 0,80,0 };
	


	//loading images is done.now we have to create a texture from it
	//create for main map
	SDL_Texture* map_tex = Texture_Creator(&rend, &map, &win);
	//creating for character : IL
	SDL_Texture* IL_tex = Texture_Creator(&rend, &IL, &win);
	//creating for character : JB
	SDL_Texture* JB_tex = Texture_Creator(&rend, &JB, &win);
	//creating for character : JS
	SDL_Texture* JS_tex = Texture_Creator(&rend, &JS, &win);
	//creating for character : JW
	SDL_Texture* JW_tex = Texture_Creator(&rend, &JW, &win);
	//creating for character : MS
	SDL_Texture* MS_tex = Texture_Creator(&rend, &MS, &win);
	//creating for character : SG
	SDL_Texture* SG_tex = Texture_Creator(&rend, &SG, &win);
	//creating for character : SH
	SDL_Texture* SH_tex = Texture_Creator(&rend, &SH, &win);
	//creating for character : WG
	SDL_Texture* WG_tex = Texture_Creator(&rend, &WG, &win);
	//creating for character : IL2
	SDL_Texture* IL2_tex = Texture_Creator(&rend, &IL2, &win);
	//creating for character : JB2
	SDL_Texture* JB2_tex = Texture_Creator(&rend, &JB2, &win);
	//creating for character : JS2
	SDL_Texture* JS2_tex = Texture_Creator(&rend, &JS2, &win);
	//creating for character : JW2
	SDL_Texture* JW2_tex = Texture_Creator(&rend, &JW2, &win);
	//creating for character : MS2
	SDL_Texture* MS2_tex = Texture_Creator(&rend, &MS2, &win);
	//creating for character : SG2
	SDL_Texture* SG2_tex = Texture_Creator(&rend, &SG2, &win);
	//creating for character : SH2
	SDL_Texture* SH2_tex = Texture_Creator(&rend, &SH2, &win);
	//creating for character : WG2
	SDL_Texture* WG2_tex = Texture_Creator(&rend, &WG2, &win);
	//creating for blocker
	SDL_Texture* blocker_tex = Texture_Creator(&rend, &blocker, &win);
	//creating for ban
	SDL_Texture* ban_tex = Texture_Creator(&rend, &ban, &win);
	//creating for light
	SDL_Texture* light_tex = Texture_Creator(&rend, &light, &win);
	//creating for light 1
	SDL_Texture* light1_tex = Texture_Creator(&rend, &light1, &win);
	//creating for light 2
	SDL_Texture* light2_tex = Texture_Creator(&rend, &light2, &win);
	//creating for light3
	SDL_Texture* light3_tex = Texture_Creator(&rend, &light3, &win);
	//creating for light4
	SDL_Texture* light4_tex = Texture_Creator(&rend, &light4, &win);
	//this part is done(i mean creating texture from images)

	//now we want to create SDL_Rect..
	//what is Rect? is a structure that has 4 elements.including width,height,x and y
	//we can adjust elements x and y in order to incept where the image should be...

	//creating the struct for main map
	SDL_Rect map_dest;
	//for IL
	SDL_Rect IL_dest;
	//for JB
	SDL_Rect JB_dest;
	//for JS
	SDL_Rect JS_dest;
	//for JW
	SDL_Rect JW_dest;
	//for MS
	SDL_Rect MS_dest;
	//for SG
	SDL_Rect SG_dest;
	//for SH
	SDL_Rect SH_dest;
	//for WG
	SDL_Rect WG_dest;
	//for IL
	SDL_Rect IL2_dest;
	//for JB
	SDL_Rect JB2_dest;
	//for JS
	SDL_Rect JS2_dest;
	//for JW
	SDL_Rect JW2_dest;
	//for MS
	SDL_Rect MS2_dest;
	//for SG
	SDL_Rect SG2_dest;
	//for SH
	SDL_Rect SH2_dest;
	//for WG
	SDL_Rect WG2_dest;
	//for blocker1
	SDL_Rect blocker1_dest;
	//for blocker 2
	SDL_Rect blocker2_dest;
	//for ban
	SDL_Rect ban_dest;
	//for ban2
	SDL_Rect ban2_dest;
	//for ban3
	SDL_Rect ban3_dest;
	//for ban4
	SDL_Rect ban4_dest;
	//for light
	SDL_Rect light_dest;
	//for light1
	SDL_Rect light1_dest;
	//for light 2
	SDL_Rect light2_dest;
	//for light 3
	SDL_Rect light3_dest;
	//for light 4
	SDL_Rect light4_dest;
	//second copy of light surface
	SDL_Rect light_dest2;
	SDL_Rect text_dest;

	//some tmp dests for lights
	SDL_Rect tmp_light1;
	SDL_Rect tmp_light2;
	SDL_Rect tmp_light3;
	SDL_Rect tmp_light4;
	SDL_Rect tmp_light;
	SDL_Rect tmp2_light;
	//some tmp dests for vent blockers
	SDL_Rect tmp_blocker1;
	SDL_Rect tmp_blocker2;

	
	
	//this part also is done!

	//loading font for our texts
	TTF_Font* font = TTF_OpenFont("D:/6) Programming/mr jack/font/black.ttf",60);

	if (font == NULL) {
		printf("cannot open ttf file");
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(rend);
		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		return 1;
	}


	char string[300] = "ability : Change your location with another character";

	
	

	SDL_Surface* text = TTF_RenderText_Solid(font, string,color);
	
	SDL_Texture* textext = Texture_Creator(&rend, &text, &win);

	//now we have to use the function SDL_QueryTexture.
	//what is QueryTexture? when we use it... it finds out width and height of the image..
	//and then assign these two value to dest.w and dest.h:
	

	//creating it for main map
	SDL_QueryTexture(map_tex, NULL, NULL, &map_dest.w, &map_dest.h);
	//for IL
	SDL_QueryTexture(IL_tex, NULL, NULL, &IL_dest.w, &IL_dest.h);
	//for JB
	SDL_QueryTexture(JB_tex, NULL, NULL, &JB_dest.w, &JB_dest.h);
	//for JS
	SDL_QueryTexture(JS_tex, NULL, NULL, &JS_dest.w, &JS_dest.h);
	//for JW
	SDL_QueryTexture(JW_tex, NULL, NULL, &JW_dest.w, &JW_dest.h);
	//for MS
	SDL_QueryTexture(MS_tex, NULL, NULL, &MS_dest.w, &MS_dest.h);
	//for SG
	SDL_QueryTexture(SG_tex, NULL, NULL, &SG_dest.w, &SG_dest.h);
	//for SH
	SDL_QueryTexture(SH_tex, NULL, NULL, &SH_dest.w, &SH_dest.h);
	//for WG
	SDL_QueryTexture(WG_tex, NULL, NULL, &WG_dest.w, &WG_dest.h);
	//for IL2
	SDL_QueryTexture(IL2_tex, NULL, NULL, &IL2_dest.w, &IL2_dest.h);
	//for JB2
	SDL_QueryTexture(JB2_tex, NULL, NULL, &JB2_dest.w, &JB2_dest.h);
	//for JS2
	SDL_QueryTexture(JS2_tex, NULL, NULL, &JS2_dest.w, &JS2_dest.h);
	//for JW2
	SDL_QueryTexture(JW2_tex, NULL, NULL, &JW2_dest.w, &JW2_dest.h);
	//for MS2
	SDL_QueryTexture(MS2_tex, NULL, NULL, &MS2_dest.w, &MS2_dest.h);
	//for SG2
	SDL_QueryTexture(SG2_tex, NULL, NULL, &SG2_dest.w, &SG2_dest.h);
	//for SH2
	SDL_QueryTexture(SH2_tex, NULL, NULL, &SH2_dest.w, &SH2_dest.h);
	//for WG2
	SDL_QueryTexture(WG2_tex, NULL, NULL, &WG2_dest.w, &WG2_dest.h);
    //for blocker
	SDL_QueryTexture(blocker_tex, NULL, NULL, &blocker1_dest.w, &blocker1_dest.h);
	//for blocker 2
	SDL_QueryTexture(blocker_tex, NULL, NULL, &blocker2_dest.w, &blocker2_dest.h);
	//for ban
	SDL_QueryTexture(ban_tex, NULL, NULL, &ban_dest.w, &ban_dest.h);
	//for ban2
	SDL_QueryTexture(ban_tex, NULL, NULL, &ban2_dest.w, &ban2_dest.h);
	//for ban3
	SDL_QueryTexture(ban_tex, NULL, NULL, &ban3_dest.w, &ban3_dest.h);
	//for ban4
	SDL_QueryTexture(ban_tex, NULL, NULL, &ban4_dest.w, &ban4_dest.h);
	//for light
	SDL_QueryTexture(light_tex, NULL, NULL, &light_dest.w, &light_dest.h);
	//for light1
	SDL_QueryTexture(light1_tex, NULL, NULL, &light1_dest.w, &light1_dest.h);
	//for light2
	SDL_QueryTexture(light2_tex, NULL, NULL, &light2_dest.w, &light2_dest.h);
	//for light3
	SDL_QueryTexture(light3_tex, NULL, NULL, &light3_dest.w, &light3_dest.h);
	//for light 4
	SDL_QueryTexture(light4_tex, NULL, NULL, &light4_dest.w, &light4_dest.h);
	SDL_QueryTexture(light_tex, NULL, NULL, &light_dest2.w, &light_dest2.h);
	//this part is done!


	//now we have to initialize each image (x,y) of the beginning point
	//map:
	map_dest.x = 0;
	map_dest.y = 0;
	//IL:
	IL_dest.h /= 6;
	IL_dest.w /= 6;
	IL_dest.x = 380;
	IL_dest.y = 365;
	//JB
	JB_dest.h /= 6.5;
	JB_dest.w /= 6.5;
	JB_dest.x = 600;
	JB_dest.y = 303;
	//JS
	JS_dest.w /= 6.4;
	JS_dest.h /= 6.4;
	JS_dest.x = 490;
	JS_dest.y = 240;
	//JW
	JW_dest.w /= 5.8;
	JW_dest.h /= 5.8;
	JW_dest.x = 160;
	JW_dest.y = 298;
	//MS
	MS_dest.w /= 6.5;
	MS_dest.h /= 6.5;
	MS_dest.x = 600;
	MS_dest.y = 547;
	//SG
	SG_dest.w /= 6.5;
	SG_dest.h /= 6.5;
	SG_dest.x = 817;
	SG_dest.y = 300;
	//SH
	SH_dest.w /= 6.5;
	SH_dest.h /= 6.5;
	SH_dest.x = 490;
	SH_dest.y = 425;
	//WG
	WG_dest.w /= 6.8;
	WG_dest.h /= 6.8;
	WG_dest.x = 380;
	WG_dest.y = 120;
	//IL2
	IL2_dest.h /= 6;
	IL2_dest.w /= 6;
	IL2_dest.x = 380;
	IL2_dest.y = 365;
	//JB2
	JB2_dest.h /= 6.5;
	JB2_dest.w /= 6.5;
	JB2_dest.x = 600;
	JB2_dest.y = 300;
	//JS2
	JS2_dest.w /= 6.4;
	JS2_dest.h /= 6.4;
	JS2_dest.x = 490;
	JS2_dest.y = 240;
	//JW2
	JW2_dest.w /= 5.5;
	JW2_dest.h /= 5.5;
	JW2_dest.x = 160;
	JW2_dest.y = 300;
	//MS2
	MS2_dest.w /= 6.5;
	MS2_dest.h /= 6.5;
	MS2_dest.x = 600;
	MS2_dest.y = 547;
	//SG2
	SG2_dest.w /= 6.6;
	SG2_dest.h /= 6.6;
	SG2_dest.x = 817;
	SG2_dest.y = 300;
	//SH2
	SH2_dest.w /= 6.5;
	SH2_dest.h /= 6.5;
	SH2_dest.x = 490;
	SH2_dest.y = 425;
	//WG2
	WG2_dest.w /= 6.8;
	WG2_dest.h /= 6.8;
	WG2_dest.x = 380;
	WG2_dest.y = 120;
	//blocker
	blocker1_dest.w /= 2.6;
	blocker1_dest.h /= 2.6;
	blocker1_dest.x = 272;
	blocker1_dest.y = 488;
	//blocker2
	blocker2_dest.w /= 2.6;
	blocker2_dest.h /= 2.6;
	blocker2_dest.x = 760;
	blocker2_dest.y = 148;
	//ban
	ban_dest.w /= 20;
	ban_dest.h /= 35;
	ban_dest.x = 760;
	ban_dest.y = 125;
	//ban2
	ban2_dest.w /= 20;
	ban2_dest.h /= 35;
	ban2_dest.x = 216;
	ban2_dest.y = 578;
	//ban3
	ban3_dest.w /= 20;
	ban3_dest.h /= 35;
	ban3_dest.x = 760;
	ban3_dest.y = 578;
	//ban4
	ban4_dest.w /= 20;
	ban4_dest.h /= 35;
	ban4_dest.x = 214;
	ban4_dest.y = 125;
	//light
	light_dest.w /= 2.8;
	light_dest.h /= 2.8;
	light_dest.x = 438;
	light_dest.y = 395;
	//light
	light_dest2.w /= 2.8;
	light_dest2.h /= 2.8;
	light_dest2.x = 545;
	light_dest2.y = 274;
	//light1
	light1_dest.w /= 2.7;
	light1_dest.h /= 2.7;
	light1_dest.x = 220;
	light1_dest.y = 460;
	//light2
	light2_dest.w /= 2.6;
	light2_dest.h /= 2.6;
	light2_dest.x = 763;
	light2_dest.y = 210;
	//light3
	light3_dest.w /= 2.6;
	light3_dest.h /= 2.6;
	light3_dest.x = 276;
	light3_dest.y = 180;
	//light4
	light4_dest.w /= 2.6;
	light4_dest.h /= 2.6;
	light4_dest.x = 708;
	light4_dest.y = 487;
	//for text
	text_dest.x = 900;
	text_dest.y = 140;
	text_dest.h = 30;
	text_dest.w = 10.125 * strlen(string);
	//making two tmp dest for bans
	SDL_Rect final1;
	SDL_Rect final2;
	//assigning values 
	final1.x = ban_dest.x;
	final1.y = ban_dest.y;
	final1.w = ban_dest.w;
	final1.h = ban_dest.h;
	final2.x = ban2_dest.x;
	final2.y = ban2_dest.y;
	final2.h = ban2_dest.h;
	final2.w = ban2_dest.w;
	//for tmp_lights
	tmp_light1.x = light1_dest.x;
	tmp_light1.y = light1_dest.y;
	tmp_light1.w = light1_dest.w;
	tmp_light1.h = light1_dest.h;
	tmp_light2.x = light2_dest.x;
	tmp_light2.y = light2_dest.y;
	tmp_light2.w = light2_dest.w;
	tmp_light2.h = light2_dest.h;
	tmp_light3.x = light3_dest.x;
	tmp_light3.y = light3_dest.y;
	tmp_light3.h = light3_dest.h;
	tmp_light3.w = light3_dest.w;
	tmp_light4.x = light4_dest.x;
	tmp_light4.y = light4_dest.y;
	tmp_light4.h = light4_dest.h;
	tmp_light4.w = light4_dest.w;
	tmp_light.x = light_dest.x;
	tmp_light.y = light_dest.y;
	tmp_light.h = light_dest.h;
	tmp_light.w = light_dest.w;
	tmp2_light.x = light_dest2.x;
	tmp2_light.y = light_dest2.y;
	tmp2_light.h = light_dest2.h;
	tmp2_light.w = light_dest2.w;
	//tmp blockers
	tmp_blocker1.x = blocker1_dest.x;
	tmp_blocker1.y = blocker1_dest.y;
	tmp_blocker1.w = blocker1_dest.w;
	tmp_blocker1.h = blocker1_dest.h;
	tmp_blocker2.x = blocker2_dest.x;
	tmp_blocker2.y = blocker2_dest.y;
	tmp_blocker2.w = blocker2_dest.w;
	tmp_blocker2.h = blocker2_dest.h;


	//creating structural array that contains info of each room
	room array[9][13];

	Map_Creator(array);

	
	
	visiblity(array);
	
	

	characters* list = (characters*)calloc(1, sizeof(characters));
	list->name[0] = 'I';
	list->name[1] = 'L';
	list->name[2] = '\0';
	list->next = (characters*)calloc(1, sizeof(characters));
	characters* current = list->next;
	current->name[0] = 'J';
	current->name[1] = 'B';
	current->name[2] = '\0';
	current->next = (characters*)calloc(1, sizeof(characters));
	current = current->next;
	current->name[0] = 'J';
	current->name[1] = 'S';
	current->name[2] = '\0';
	current->next = calloc(1, sizeof(characters));
	current = current->next;
	current->name[0] = 'J';
	current->name[1] = 'W';
	current->name[2] = '\0';
	current->next = (characters*)calloc(1, sizeof(characters));
	current = current->next;
	current->name[0] = 'M';
	current->name[1] = 'S';
	current->name[2] = '\0';
	current->next = (characters*)calloc(1, sizeof(characters));
	current = current->next;
	current->name[0] = 'S';
	current->name[1] = 'G';
	current->name[2] = '\0';
	current->next = (characters*)calloc(1, sizeof(characters));
	current = current->next;
	current->name[0] = 'S';
	current->name[1] = 'H';
	current->name[2] = '\0';
	current->next = (characters*)calloc(1, sizeof(characters));
	current = current->next;
	current->name[0] = 'W';
	current->name[1] = 'G';
	current->name[2] = '\0';
	current->next = NULL;

	characters* list1 = (characters*)calloc(1, sizeof(characters));
	characters* list2 = (characters*)calloc(1, sizeof(characters));
	list1->next = (characters*)calloc(1, sizeof(characters));
	list1->next->next = (characters*)calloc(1, sizeof(characters));
	list1->next->next->next = (characters*)calloc(1, sizeof(characters));
	list1->next->next->next->next = NULL;
	list2->next = (characters*)calloc(1, sizeof(characters));
	list2->next->next = (characters*)calloc(1, sizeof(characters));
	list2->next->next->next = (characters*)calloc(1, sizeof(characters));
	list2->next->next->next->next = NULL;
	

	
	

	
	linked_list_shuffle(&list, &list1, &list2);

	
	
	
	

	SDL_Event event;
	bool running = 1;

	bool mr_jack_win;
	bool mrjacks_turn;
	bool detectors_turn;


	int dast = 0;

	char first2;
	char second2;

	char finaling[3];

	bool tamam = 1;
	
	
	while (running && tamam == 1) {
		visiblity(array);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			running = 0;
			text_displayer("good luck", font, color, rend);
			SDL_RenderPresent(rend);
			SDL_Delay(1000);
		}
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
		SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
		SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
		SDL_RenderCopy(rend, ban_tex, NULL, &final1);
		SDL_RenderCopy(rend, ban_tex, NULL, &final2);
		SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
		SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
		SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
		SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
		SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
		SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
		SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
		SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
		SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
		SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
		SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
		SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
		SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
		SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);

		SDL_RenderPresent(rend);
		SDL_Delay(1000 / 60);
		if (dast == 0) {
			srand(time(0));
			int random = rand() % 8 + 1;
			characters* current = list;
			for (int i = 0; i < random - 1; i++) {
				current = current->next;
			}
			first2 = current->name[0];
			second2 = current->name[1];
			
			printf("WARNING: Asking detector not to see the screen\n");
			printf("mr jacks character will be unveiled in 5 second:\n");
			SDL_Delay(5000);
			printf("Alright, mr jack's character is :\n");
			printf("%c%c\n", first2, second2);
			printf("\n\n\n\n\n\n\n\n\n\n");
			dast++;
		}



		if (dast == 1) {
			printf("     ROUND1     : \n");
			
			linked_list_shuffle(&list, &list1, &list2);
		}
		else if (dast == 5) {
			visiblity_checker(array, first2, second2, &IL_tex, &MS_tex, &SH_tex, &JW_tex, &JS_tex, &JB_tex, &SG_tex, &WG_tex, IL2_tex, MS2_tex, SG2_tex, JB2_tex, JS2_tex, JW2_tex, WG2_tex, SH2_tex);
			printf("     ROUND2     : \n");
		}
		else if (dast == 9) {
			printf("     ROUND3     : \n");
			linked_list_shuffle(&list, &list1, &list2);
		}
		else if (dast == 13) {
			printf("     ROUND4     : \n");
		}
		else if (dast == 17) {
			printf("     ROUND5     : \n");
			linked_list_shuffle(&list, &list1, &list2);
		}
		else if (dast == 21) {
			printf("     ROUND6     : \n");
		}
		else if (dast == 25) {
			printf("     ROUND7     : \n");
			linked_list_shuffle(&list, &list1, &list2);
		}
		else if (dast == 29) {
			printf("     ROUND8     : \n");
		}
		else if (dast == 33) {
			break;
		}
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
		SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
		SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
		SDL_RenderCopy(rend, ban_tex, NULL, &final1);
		SDL_RenderCopy(rend, ban_tex, NULL, &final2);
		SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
		SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
		SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
		SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
		SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
		SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
		SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
		SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
		SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
		SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
		SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
		SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
		SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
		SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);

		SDL_RenderPresent(rend);


		if (dast % 4 == 1 || dast % 4 == 0) {
			printf("Its detector's turn: \n");
			detectors_turn = 1;
			mrjacks_turn = 0;
		}
		else {
			printf("Its mr.jack's turn\n");
			mrjacks_turn = 0;
			detectors_turn = 1;
		}

		printf("witch character do you want to choose between these below: \n");


		if ((int)floor((double)(dast - 1) / 4) % 2 == 0) {
			int i = 1;
			for (characters* current = list1; current != NULL; current = current->next) {
				printf("%d) %s   ", i, current->name);
				i++;
			}
			printf("\n");


		}
		else {
			int i = 1;
			for (characters* current = list2; current != NULL; current = current->next) {
				printf("%d) %s   ", i, current->name);
			}
			printf("\n");
		}

		char character[3];
		for (int i = 0; i < 2; i++) {
			character[i] = '\0';
		}

		bool in_list = 0;
		while (in_list == 0) {

			

			gets(character);


			

			if ((int)floor((double)(dast - 1) / 4) % 2 == 0) {
				for (characters* current = list1; current != NULL; current = current->next) {
					if (strcmp(current->name, character) == 0) {
						in_list = 1;
					}
				}
			}
			else {
				for (characters* current = list2; current != NULL; current = current->next) {
					if (strcmp(current->name, character) == 0) {
						in_list = 1;
					}
				}
			}

			if (in_list == 0) {
				printf("Not in list! try again\n");
			}

		}

		if (strcmp(character, "IL") == 0) {

			if (mrjacks_turn == 1 && first2 == 'I' && second2 == 'L') {
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 13; j++) {
						if (strcmp(array[i][j].name, "IL") == 0) {
							if (array[i][j].escape == 1) {
								printf("WANRNING: you can escape by pressing E:");
								char escape = NULL;
								scanf_s("%c", &escape);
								if (escape == 'E') {
									printf("mr jack won. the game is over.\n");
								}
							}
						}
					}
				}
			}

			dast++;
			bool ability = 0;
			bool movement2 = 0;
			while (!(ability == 1 && movement2 == 1)) {
				if (detectors_turn == 1) {
					printf("catch by pressing 'H'\n");
				}
				printf("to change the road blocker , press F: \n");
				printf("to move , use M : \n");
				char operation;
				scanf_s("%c", &operation);
				if (operation == 'F' && ability == 0) {
					printf("which way do you want to be opened? \n");
					printf("it can be perceived by telling x & y of the escape room : ");
					int i;
					int j;
					scanf_s("%d %d", &i, &j);
					printf("and which way do you want to be closed? \n");
					int i2;
					int j2;
					scanf_s("%d %d", &i2, &j2);



					printf("is %d\n", final1.x);
					if (IL_Ability(i, j, i2, j2, array, &ban_dest, &ban2_dest, &ban3_dest, &ban4_dest, &final1, &final2) == 0) {
						ability = 1;
					}

					else {
						printf("you have entered wrong inputs, try again");
					}
					printf("is %d\n", final1.x);
					SDL_RenderClear(rend);
					SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
					SDL_RenderCopy(rend, ban_tex, NULL, &final1);
					SDL_RenderCopy(rend, ban_tex, NULL, &final2);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
					SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
					SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
					SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
					SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
					SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
					SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
					SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
					SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
					SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
					SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
					SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
					SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
					SDL_RenderPresent(rend);
				}
				else if (operation == 'M' && movement2 == 0) {
					movement2 = 1;
					int counter = 1;
					int first;
					int second;
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 13; j++) {
							if (array[i][j].name[0] == 'I' && array[i][j].name[1] == 'L') {
								first = i;
								second = j;
							}
						}
					}
					while (counter < 4) {
						movement(array, "IL", &IL_dest, &counter, first, second);
						SDL_RenderClear(rend);
						SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
						SDL_RenderCopy(rend, ban_tex, NULL, &final1);
						SDL_RenderCopy(rend, ban_tex, NULL, &final2);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
						SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
						SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
						SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
						SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
						SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
						SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
						SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
						SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
						SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
						SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
						SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
						SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
						SDL_RenderPresent(rend);
					}
				}
				if (operation == 'H') {
					etmam("IL", array, finaling);
					tamam = 0;
				}
			}
		}
		else if (strcmp(character, "SH") == 0) {
		if (mrjacks_turn == 1 && first2 == 'S' && second2 == 'H') {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "SH") == 0) {
						if (array[i][j].escape == 1) {
							printf("WANRNING: you can escape by pressing E:");
							char escape = NULL;
							scanf_s("%c", &escape);
							if (escape == 'E') {
								printf("mr jack won. the game is over.\n");
							}
						}
					}
				}
			}
		}
			dast++;
			int first;
			int second;
			if (detectors_turn == 1) {
				printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
				char choose = '\0';
				scanf_s("%c", &choose);
				if (choose == 'Y') {
					etmam("SH", array, finaling);
					tamam = 0;
				}
			}
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (array[i][j].name[0] == 'S' && array[i][j].name[1] == 'H') {
						first = i;
						second = j;
					}
				}
			}
			printf("first, you have to move then you can use your ability.\n");
			int counter = 1;
			while (counter < 4) {
				movement(array, "SH", &SH_dest, &counter, first, second);
				SDL_RenderClear(rend);
				SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
				SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
				SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
				SDL_RenderCopy(rend, ban_tex, NULL, &final1);
				SDL_RenderCopy(rend, ban_tex, NULL, &final2);
				SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
				SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
				SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
				SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
				SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
				SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
				SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
				SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
				SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
				SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
				SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
				SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
				SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
				SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
				SDL_RenderPresent(rend);
			}

			printf("now you can use your ability by pressing F :\n");
			char Ability = NULL;
			while (Ability != 'F') {

				scanf_s("%c", &Ability);
				getchar();
				if (Ability != 'F') {
					printf("Wrong input");
				}
				else {
					SH_Ability(&list, &IL_tex, IL2_tex, &MS_tex, MS2_tex, &SH_tex, SH2_tex, &JS_tex, JS2_tex, &JW_tex, JW2_tex, &SG_tex, SG2_tex, &WG_tex, WG2_tex, &JB_tex, JB2_tex, first2, second2);
					SDL_RenderClear(rend);
					SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
					SDL_RenderCopy(rend, ban_tex, NULL, &final1);
					SDL_RenderCopy(rend, ban_tex, NULL, &final2);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
					SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
					SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
					SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
					SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
					SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
					SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
					SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
					SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
					SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
					SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
					SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
					SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
					SDL_RenderPresent(rend);
				}

			}

		}
		else if (strcmp(character, "WG") == 0) {
		if (mrjacks_turn == 1 && first2 == 'W' && second2 == 'G') {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "WG") == 0) {
						if (array[i][j].escape == 1) {
							printf("WANRNING: you can escape by pressing E:");
							char escape = NULL;
							scanf_s("%c", &escape);
							if (escape == 'E') {
								printf("mr jack won. the game is over.\n");
							}
						}
					}
				}
			}
		}
		dast++;
		if (detectors_turn == 1) {
			printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
			char choose = '\0';
			scanf_s("%c", &choose);
			if (choose == 'Y') {
				etmam("WG", array, finaling);
				tamam = 0;
			}
		}
			printf("you can move 1 to 3 hexes or you can use ability\n");
			printf("you can move by pressing 'M' or using ability by pressing F :\n");
			char choose;

			scanf_s("%c", &choose);

			int first;
			int second;
			int counter = 1;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "WG") == 0) {
						first = i;
						second = j;
					}
				}
			}

			if (choose == 'F') {
				printf("wanna exchange? by which one?\n");
				int x;
				int y;
				bool finish = 0;
				SDL_Rect* tmp = NULL;
				while (finish == 0) {
					scanf_s("%d %d", &x, &y);

					if (strcmp(array[x - 1][y - 1].name, "IL") == 0) {
						tmp = &IL_dest;
						finish = 1;
					}
					else if (strcmp(array[x - 1][y - 1].name, "JW") == 0) {
						tmp = &JW_dest;
						finish = 1;
					}
					else if (strcmp(array[x - 1][y - 1].name, "SH") == 0) {
						tmp = &SH_dest;
						finish = 1;
					}
					else if (strcmp(array[x - 1][y - 1].name, "JB") == 0) {
						tmp = &JB_dest;
						finish = 1;
					}
					else if (strcmp(array[x - 1][y - 1].name, "JS") == 0) {
						tmp = &JS_dest;
						finish = 1;
					}
					else if (strcmp(array[x - 1][y - 1].name, "MS") == 0) {
						tmp = &MS_dest;
						finish = 1;
					}
					else if (strcmp(array[x - 1][y - 1].name, "SG") == 0) {
						tmp = &SG_dest;
						finish = 1;
					}
					if (finish == 0) {
						printf("wrong input\n");
					}
				}
				WG_Ability(&WG_dest, tmp);
				char tmp1;
				char tmp2;
				tmp1 = array[first][second].name[0];
				tmp2 = array[first][second].name[1];
				array[first][second].name[0] = array[x - 1][y - 1].name[0];
				array[first][second].name[1] = array[x - 1][y - 1].name[1];
				array[x - 1][y - 1].name[0] = tmp1;
				array[x - 1][y - 1].name[1] = tmp2;
				printf("done\n");
			}
			else if (choose == 'M') {

				while (counter < 4) {
					movement(array, "WG", &WG_dest, &counter, first, second);
					SDL_RenderClear(rend);
					SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
					SDL_RenderCopy(rend, ban_tex, NULL, &final1);
					SDL_RenderCopy(rend, ban_tex, NULL, &final2);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
					SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
					SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
					SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
					SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
					SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
					SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
					SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
					SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
					SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
					SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
					SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
					SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
					SDL_RenderPresent(rend);
				}
			}
		}
		else if (strcmp(character, "JS") == 0) {
		if (mrjacks_turn == 1 && first2 == 'J' && second2 == 'S') {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "JS") == 0) {
						if (array[i][j].escape == 1) {
							printf("WANRNING: you can escape by pressing E:");
							char escape = NULL;
							scanf_s("%c", &escape);
							if (escape == 'E') {
								printf("mr jack won. the game is over.\n");
							}
						}
					}
				}
			}
		}
		dast++;
		if (detectors_turn == 1) {
			printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
			char choose = '\0';
			scanf_s("%c", &choose);
			if (choose == 'Y') {
				etmam("JS", array, finaling);
				tamam = 0;
			}
		}
			bool ability = 0;
			bool movement2 = 0;
			while (!(ability == 1 && movement2 == 1)) {
				printf("to use ability, you can press F:\n");
				printf("to move, you can press M: \n");
				char choose;
				scanf_s("%c", &choose);
				if (choose == 'F' && ability == 0) {
					printf("which light do you want to move?\n");
					int i;
					int j;
					scanf_s("%d %d", &i, &j);
					printf("and to where?\n");
					int i2;
					int j2;
					scanf_s("%d %d", &i2, &j2);
					if (JS_Ability(i, j, i2, j2, array, &light1_dest, &light2_dest, &light3_dest, &light4_dest, &light_dest, &light_dest2, &tmp_light1, &tmp_light1, &tmp_light2, &tmp_light3, &tmp_light4, &tmp_light, &tmp2_light) == 0) {
						SDL_RenderClear(rend);
						SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
						SDL_RenderCopy(rend, ban_tex, NULL, &final1);
						SDL_RenderCopy(rend, ban_tex, NULL, &final2);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
						SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
						SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
						SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
						SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
						SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
						SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
						SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
						SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
						SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
						SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
						SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
						SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
						SDL_RenderPresent(rend);
						ability = 1;
						printf("done\n");
					}

				}
				else if (choose == 'M' && movement2 == 0) {
					int counter = 1;
					int first;
					int second;
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 13; j++) {
							if (array[i][j].name[0] == 'J' && array[i][j].name[1] == 'S') {
								first = i;
								second = j;
							}
						}
					}
					while (counter < 4) {
						movement(array, "JS", &JS_dest, &counter, first, second);
						SDL_RenderClear(rend);
						SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
						SDL_RenderCopy(rend, ban_tex, NULL, &final1);
						SDL_RenderCopy(rend, ban_tex, NULL, &final2);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
						SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
						SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
						SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
						SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
						SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
						SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
						SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
						SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
						SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
						SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
						SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
						SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
						SDL_RenderPresent(rend);
					}
					movement2 = 1;
				}
			}


		}
		else if (strcmp(character, "MS") == 0) {
		if (mrjacks_turn == 1 && first2 == 'M' && second2 == 'S') {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "MS") == 0) {
						if (array[i][j].escape == 1) {
							printf("WANRNING: you can escape by pressing E:");
							char escape = NULL;
							scanf_s("%c", &escape);
							if (escape == 'E') {
								printf("mr jack won. the game is over.\n");
							}
						}
					}
				}
			}
		}
		dast++;
		if (detectors_turn == 1) {
			printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
			char choose = '\0';
			scanf_s("%c", &choose);
			if (choose == 'Y') {
				etmam("MS", array, finaling);
				tamam = 0;
			}
		}
			printf("attention: you can sneaky go into the houses and then leave them out,but you cannot stay inside the houses.\n");
			int first;
			int second;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (array[i][j].name[0] == 'M' && array[i][j].name[1] == 'S') {
						first = i;
						second = j;
					}
				}
			}
			int counter = 1;
			while (counter < 5) {
				MS_Ability(array, "MS", &MS_dest, &counter, first, second);
				SDL_RenderClear(rend);
				SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
				SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
				SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
				SDL_RenderCopy(rend, ban_tex, NULL, &final1);
				SDL_RenderCopy(rend, ban_tex, NULL, &final2);
				SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
				SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
				SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
				SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
				SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
				SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
				SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
				SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
				SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
				SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
				SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
				SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
				SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
				SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
				SDL_RenderPresent(rend);
			}
		}

		else if (strcmp(character, "JB") == 0) {
		if (mrjacks_turn == 1 && first2 == 'J' && second2 == 'B') {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "JB") == 0) {
						if (array[i][j].escape == 1) {
							printf("WANRNING: you can escape by pressing E:");
							char escape = NULL;
							scanf_s("%c", &escape);
							if (escape == 'E') {
								printf("mr jack won. the game is over.\n");
							}
						}
					}
				}
			}
		}
		dast++;
		if (detectors_turn == 1) {
			printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
			char choose = '\0';
			scanf_s("%c", &choose);
			if (choose == 'Y') {
				etmam("JB", array, finaling);
				tamam = 0;
			}
		}
			bool ability = 0;
			bool movement2 = 0;
			while (!(ability == 1 && movement2 == 1)) {
				
				printf("you can change the blockers and you can move.\n");
				printf("to move, press 'M'\n");
				printf("to use ability, press F:\n");
				char choose;
				scanf_s("%c", &choose);
				if (choose == 'F' && ability == 0) {
					ability = 1;
					printf("which blocker's destination do you want to be changed?:\n");
					int i;
					int j;
					scanf_s("%d %d", &i, &j);
					printf("and where do you want it to go?:\n");
					int i2;
					int j2;
					scanf_s("%d %d", &i2, &j2);
					if (JB_Ability(i, j, i2, j2, array, &tmp_blocker1, &tmp_blocker2) == 0) {
						ability = 1;
					}
					else {
						printf("there is something wrong with your inputs.\n");
					}
					SDL_RenderClear(rend);
					SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
					SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
					SDL_RenderCopy(rend, ban_tex, NULL, &final1);
					SDL_RenderCopy(rend, ban_tex, NULL, &final2);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
					SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
					SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
					SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
					SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
					SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
					SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
					SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
					SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
					SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
					SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
					SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
					SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
					SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
					SDL_RenderPresent(rend);

				}

				else if (choose == 'M' && movement2 == 0) {
					movement2 = 1;
					int first;
					int second;

					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 13; j++) {
							if (array[i][j].name[0] == 'J' && array[i][j].name[1] == 'B') {
								first = i;
								second = j;
							}
						}
					}
					int counter = 1;
					while (counter < 4) {
						movement(array, "JB", &JB_dest, &counter, first, second);
						SDL_RenderClear(rend);
						SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
						SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
						SDL_RenderCopy(rend, ban_tex, NULL, &final1);
						SDL_RenderCopy(rend, ban_tex, NULL, &final2);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
						SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
						SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
						SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
						SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
						SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
						SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
						SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
						SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
						SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
						SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
						SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
						SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
						SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
						SDL_RenderPresent(rend);
					}
				}
			}

		}
		else if (strcmp(character, "SG") == 0) {
		if (mrjacks_turn == 1 && first2 == 'S' && second2 == 'G') {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 13; j++) {
					if (strcmp(array[i][j].name, "SG") == 0) {
						if (array[i][j].escape == 1) {
							printf("WANRNING: you can escape by pressing E:");
							char escape = NULL;
							scanf_s("%c", &escape);
							if (escape == 'E') {
								printf("mr jack won. the game is over.\n");
							}
						}
					}
				}
			}
		}
			if (detectors_turn == 1) {
				printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
				char choose = '\0';
				scanf_s("%c", &choose);
				if (choose == 'Y') {
					etmam("SG", array, finaling);
					tamam = 0;
				}
			}
				dast++;
				if (detectors_turn == 1) {
					printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!");
					char choose = '\0';
					scanf_s("%c", &choose);
					if (choose == 'Y') {
						etmam("SG", array, finaling);
						tamam = 0;
					}
					printf("you can both move and change characters place.\n");
					printf("press 'M' to move yourself\n");
					printf("press 'F' to use the ability\n");
					bool ability = 0;
					bool movement2 = 0;
					while (!(ability == 1 && movement2 == 1)) {
						printf("you can move 3 hexes at all.\n");
						char choose;
						scanf_s("%c", &choose);
						if (choose == 'M' && movement2 == 0) {
							movement2 = 1;
							int first;
							int second;
							int counter = 1;
							for (int i = 0; i < 9; i++) {
								for (int j = 0; j < 13; j++) {
									if (array[i][j].name[0] == 'S' && array[i][j].name[1] == 'G') {
										first = i;
										second = j;
									}
								}
							}
							while (counter < 4) {
								movement(array, "SG", &SG_dest, &counter, first, second);
								SDL_RenderClear(rend);
								SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
								SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
								SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
								SDL_RenderCopy(rend, ban_tex, NULL, &final1);
								SDL_RenderCopy(rend, ban_tex, NULL, &final2);
								SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
								SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
								SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
								SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
								SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
								SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
								SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
								SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
								SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
								SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
								SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
								SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
								SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
								SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
								SDL_RenderPresent(rend);
							}
						}
						else if (choose == 'F' && ability == 0) {
							ability = 1;
							getchar();
							int counter = 1;
							while (counter < 4) {
								printf("pick up character you want to move:\n");
								char choose[3];
								gets(choose);
								if (strcmp(choose, "WG") == 0) {
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'W' && array[i][j].name[1] == 'G') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "WG", &WG_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}
								else if (strcmp(choose, "JS") == 0) {
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'J' && array[i][j].name[1] == 'S') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "JS", &JS_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}
								if (strcmp(choose, "JW") == 0) {
									if (mrjacks_turn == 1 && first2 == 'I' && second2 == 'L') {
										for (int i = 0; i < 9; i++) {
											for (int j = 0; j < 13; j++) {
												if (strcmp(array[i][j].name, "IL") == 0) {
													if (array[i][j].escape == 1) {
														printf("WANRNING: you can escape by pressing E:");
														char escape = NULL;
														scanf_s("%c", &escape);
														if (escape == 'E') {
															printf("mr jack won. the game is over.\n");
														}
													}
												}
											}
										}
									}
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'J' && array[i][j].name[1] == 'W') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "JW", &JW_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}
								if (strcmp(choose, "MS") == 0) {
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'M' && array[i][j].name[1] == 'S') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "MS", &MS_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}
								if (strcmp(choose, "IL") == 0) {
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'I' && array[i][j].name[1] == 'L') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "IL", &IL_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}
								if (strcmp(choose, "JB") == 0) {
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'J' && array[i][j].name[1] == 'B') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "JB", &JB_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}
								if (strcmp(choose, "SH") == 0) {
									int first;
									int second;
									for (int i = 0; i < 9; i++) {
										for (int j = 0; j < 13; j++) {
											if (array[i][j].name[0] == 'S' && array[i][j].name[1] == 'H') {
												first = i;
												second = j;
											}
										}
									}
									movement(array, "SH", &SH_dest, &counter, first, second);
									SDL_RenderClear(rend);
									SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
									SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
									SDL_RenderCopy(rend, ban_tex, NULL, &final1);
									SDL_RenderCopy(rend, ban_tex, NULL, &final2);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
									SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
									SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
									SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
									SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
									SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
									SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
									SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
									SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
									SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
									SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
									SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
									SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
									SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
									SDL_RenderPresent(rend);

								}

							}
						}
					}
				}
				else if (strcmp(character, "JW") == 0) {
					if (detectors_turn == 1) {
						printf("you can catch characters next to you. say 'Y if you want, if not, say 'N'!\n");
						char choose = '\0';
						scanf_s("%c", &choose);
						if (choose == 'Y') {
							etmam("JW", array, finaling);
							tamam = 0;
						}
					}
						dast++;
						printf("you can move by this character\n");
						int first;
						int second;
						for (int i = 0; i < 9; i++) {
							for (int j = 0; j < 13; j++) {
								if (array[i][j].name[0] == 'J' && array[i][j].name[1] == 'S') {
									first = i;
									second = j;
								}
							}
						}
						int counter = 1;
						while (counter < 4) {
							movement(array, "JW", &JW_dest, &counter, first, second);
							SDL_RenderClear(rend);
							SDL_RenderCopy(rend, map_tex, NULL, &map_dest);
							SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker1);
							SDL_RenderCopy(rend, blocker_tex, NULL, &tmp_blocker2);
							SDL_RenderCopy(rend, ban_tex, NULL, &final1);
							SDL_RenderCopy(rend, ban_tex, NULL, &final2);
							SDL_RenderCopy(rend, light_tex, NULL, &tmp_light);
							SDL_RenderCopy(rend, light_tex, NULL, &tmp2_light);
							SDL_RenderCopy(rend, light1_tex, NULL, &tmp_light1);
							SDL_RenderCopy(rend, light2_tex, NULL, &tmp_light2);
							SDL_RenderCopy(rend, light3_tex, NULL, &tmp_light3);
							SDL_RenderCopy(rend, light4_tex, NULL, &tmp_light4);
							SDL_RenderCopy(rend, WG_tex, NULL, &WG_dest);
							SDL_RenderCopy(rend, JS_tex, NULL, &JS_dest);
							SDL_RenderCopy(rend, JB_tex, NULL, &JB_dest);
							SDL_RenderCopy(rend, JW_tex, NULL, &JW_dest);
							SDL_RenderCopy(rend, SH_tex, NULL, &SH_dest);
							SDL_RenderCopy(rend, SG_tex, NULL, &SG_dest);
							SDL_RenderCopy(rend, MS_tex, NULL, &MS_dest);
							SDL_RenderCopy(rend, IL_tex, NULL, &IL_dest);
							SDL_RenderPresent(rend);
						}


					}

					delete_node(&list1, character);
					delete_node(&list2, character);
				}
}

                


if (dast == 33) {
	printf("mr jack won\n");
}
else if (tamam == 0) {
	if (finaling[0] == first2 && finaling[1] == second2) {
		printf("detector won\n");
	}
	else {
		printf("mr jack won\n");
	}
}
				 












				return 0;

			}
		

//assigning types of each room(building,vent,light,outside,empty...)



SDL_Surface* Surface_Creator(char address[200], SDL_Window** win, SDL_Renderer** rend) {
	SDL_Surface* surf = IMG_Load(address);
	if (surf == NULL) {
		printf("cannor create surface due to error : %s\n", SDL_GetError());
		SDL_DestroyWindow(*win);
		SDL_DestroyRenderer(*rend);
		SDL_Quit();
		return 1;
	}

	return surf;
}


SDL_Texture* Texture_Creator(SDL_Renderer** rend, SDL_Surface** surface,SDL_Window** window) {
	SDL_Texture* tex = SDL_CreateTextureFromSurface(*rend, *surface);
	SDL_FreeSurface(*surface);
	if (tex == NULL) {
		printf("Cannot create texture due to error : %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*rend);
		SDL_Quit();
		return 1;
	}


	return tex;
}


void text_displayer(char string[500],TTF_Font* font,SDL_Color color,SDL_Renderer* rend) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, string, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_Rect tex_dest;
	tex_dest.h = 30;
	tex_dest.w = 10.125 * strlen(string);
	tex_dest.x = 900;
	tex_dest.y = 140;

	SDL_RenderCopy(rend, tex, NULL, &tex_dest);

}

void linked_list_shuffle(characters** list,characters** list2,characters** list3) {
	srand(time(0));
	

	for (int i = 0; i < 10; i++) {
		int a = rand() %8 + 1 ;
		int b = rand() %8 + 1 ;
		if (a == 1) {
			characters* current2 = *list;
			for (int i = 0; i < b - 2; i++) {
				current2 = current2->next;
			}
			characters* tmp = current2->next;
			characters* tmp2 = current2->next->next;
			current2->next = *list;
			characters* tmp1 = (*list)->next;
			*list = tmp;
			(*list)->next = tmp1;
			current2->next->next = tmp2;
		}
		else if (b == 1) {
			characters* current2 = *list;
			for (int i = 0; i < a - 2; i++) {
				current2 = current2->next;
			}
			characters* tmp = current2->next;
			characters* tmp2 = current2->next->next;
			current2->next = *list;
			characters* tmp1 = (*list)->next;
			*list = tmp;
			(*list)->next = tmp1;
			current2->next->next = tmp2;
		}
		else {
			characters* current1 = *list;
			characters* current2 = *list;
			int tmp4 = a;
			a = min(a, b);
			b = max(tmp4, b);
			for (int i = 0; i < b - 2; i++) {
				current1 = current1->next;
			}
			for (int i = 0; i < a - 2; i++) {
				current2 = current2->next;
			}
			characters* tmp = current1->next->next;
			characters* tmp1 = current1->next;
			current1->next = current2->next;
			characters* tmp2 = current2->next->next;
			current1->next->next = tmp;
			current2->next = tmp1;
			current2->next->next = tmp2;
		}

	}
	(*list2) = NULL;
	(*list3) = NULL;
	(*list2) = (characters*)calloc(1, sizeof(characters));
	(*list3) = (characters*)calloc(1, sizeof(characters));
	(* list2)->next = (characters*)calloc(1, sizeof(characters));
	(* list2)->next->next = (characters*)calloc(1, sizeof(characters));
	(* list2)->next->next->next = (characters*)calloc(1, sizeof(characters));
	(* list2)->next->next->next->next = NULL;
	(* list3)->next = (characters*)calloc(1, sizeof(characters));
	(* list3)->next->next = (characters*)calloc(1, sizeof(characters));
	(* list3)->next->next->next = (characters*)calloc(1, sizeof(characters));
	(* list3)->next->next->next->next = NULL;
	characters* operation = *list;
	characters* operation1 = *list2;
	characters* operation2 = *list3;
	for (int i = 0; i < 4; i++) {
		operation1->name[0] = operation->name[0];
		operation1->name[1] = operation->name[1];
		operation = operation->next;
		operation1 = operation1->next;
	}
	for (int i = 0; i < 4; i++) {
		operation2->name[0] = operation->name[0];
		operation2->name[1] = operation->name[1];
		operation = operation->next;
		operation2 = operation2->next;
	}
}

void where_is_mr_jack(char first, char second,room array[9][13]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (array[i][j].name[0] == first && array[i][j].name[1] == second) {
				array[i][j].mr_jack = 1;
			}
		}
	}
}


void delete_node(characters** list,char name[3]) {
	if (strcmp((*list)->name, name) == 0) {
		*list = (*list)->next;
	}
	else {
		characters* current;
		for (current = *list; current->next != NULL; current = current->next) {
			if (strcmp(current->next->name, name) == 0) {
				current->next = current->next->next;
				break;
			}
		}
	}
	
}

void movement(room array[9][13], char name[3],SDL_Rect* dest , int * i, int first, int second) {
	int tmp1;
	int tmp2;
	

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (strcmp(name, array[i][j].name) == 0) {
				tmp1 = i;
				tmp2 = j;
			}
		}
	}

	printf("OK, now where you wanna go/do by this character?\n\n");
	
	printf("WARNING : remember, you have only 3 chances to make your move : \n");
	printf("HINT : to go up , press 'W'.\n ");
	printf("to go down , press 'S'. \n ");
	printf(" to go left down , press 'SA'. \n");
	printf(" to go left up , press 'WA'. \n");
	printf(" to go right up , press 'WD'. \n");
	printf("to go right down , press 'SD'. \n\n");
	printf("to use vent, press 'V' :\n");
	printf("Whenever your choice is done , hit enter to continue. \n");
	printf("you can stop moving by pressing 'C':\n");

	

	char move[3];
	
	

	gets(move);

	if (*i > 1 && strcmp(move, "C") == 0) {
		*i = 4;
			return;
	}
	else if (*i == 1 && strcmp(move, "C") == 0) {
		printf("you have to move at least 1 hex.\n");
	}
	
	if (tmp2 % 2 == 1) {
		if (strcmp(move, "WA") == 0 && tmp2 - 1 >= 0) {
			if (array[tmp1][tmp2 - 1].type != 4 && array[tmp1][tmp2 - 1].type != 1 &&  !(array[tmp1][tmp2 - 1].name[0] != 'N') && !(tmp1 == first && tmp2 - 1 == second)) {
				array[tmp1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x -= 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "WD") == 0 && tmp2 + 1 <= 13) {
			if (array[tmp1][tmp2 + 1].type != 4 && array[tmp1][tmp2 + 1].type != 1 && !(array[tmp1][tmp2 + 1].name[0] != 'N') && !(tmp1 == first && tmp2+1 == second) ) {
				array[tmp1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x += 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "SA") == 0 && tmp2 - 1 >= 0 && tmp1 + 1 <= 9) {
			if (array[tmp1+1][tmp2 -1].type != 4 && array[tmp1+1][tmp2-1].type != 1 && !(array[tmp1 + 1][tmp2 - 1].name[0] != 'N') && !(tmp1 + 1== first && tmp2 - 1 == second)) {
				array[tmp1+1][tmp2-1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1+1][tmp2-1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 30;
				dest->x -= 55;
				(*i)++;
			}
		}
		else if (strcmp(move, "SD") == 0 && tmp2 + 1<= 13 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2 + 1].type != 4 && array[tmp1 + 1][tmp2 + 1].type != 1 && !(array[tmp1 + 1][tmp2 + 1].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 + 1 == second)) {
				array[tmp1 + 1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 30;
				dest->x += 55;
				(*i)++;
			}
		}
		else if (strcmp(move, "S") == 0 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2].type != 4 && array[tmp1 + 1][tmp2].type != 1 && !(array[tmp1 + 1][tmp2].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 == second)) {
				array[tmp1 + 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 61;
				(*i)++;
			}
		}
		else if (strcmp(move, "W") == 0 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2].type != 4 && array[tmp1 - 1][tmp2].type != 1 && !(array[tmp1 - 1][tmp2].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 == second)) {
				array[tmp1 - 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y -= 61;
				(*i)++;
			}
		}
	}

	else {
		if (strcmp(move, "WA") == 0 && tmp2 - 1 >= 0 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2 - 1].type != 4 && array[tmp1 - 1][tmp2 - 1].type != 1 && !(array[tmp1 - 1][tmp2 - 1].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 - 1 == second)) {
				array[tmp1 - 1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x -= 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "WD") == 0 && tmp2 + 1 <= 13 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2 + 1].type != 4 && array[tmp1 - 1][tmp2 + 1].type != 1 && !(array[tmp1 - 1][tmp2 + 1].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 + 1 == second)) {
				array[tmp1 - 1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x += 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "SA") == 0 && tmp2 - 1 >= 0) {
			if (array[tmp1][tmp2 - 1].type != 4 && array[tmp1][tmp2 - 1].type != 1 && !(array[tmp1][tmp2 - 1].name[0] != 'N') && !(tmp1 == first && tmp2 - 1 == second)) {
				array[tmp1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x -= 55;
				dest->y += 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "SD") == 0 && tmp2 + 1 <= 13) {
			if (array[tmp1][tmp2 + 1].type != 4 && array[tmp1][tmp2 + 1].type != 1 && !(array[tmp1][tmp2 + 1].name[0] != 'N') && !(tmp1 == first && tmp2 + 1 == second)) {
				array[tmp1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x += 55;
				dest->y += 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "S") == 0 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2].type != 4 && array[tmp1 + 1][tmp2].type != 1 && !(array[tmp1 + 1][tmp2].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 == second)) {
				array[tmp1 + 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 61;
				(*i)++;
			}
		}
		else if (strcmp(move, "W") == 0 && tmp1 - 1 >= 0 && !(array[tmp1 - 1][tmp2].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 == second)) {
			
			if (array[tmp1 - 1][tmp2].type != 4 && array[tmp1 - 1][tmp2].type != 1) {
				array[tmp1 - 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y -= 61;
				(* i)++;
			}
		}
	}

	if (strcmp(move, "V") == 0) {
		if (array[tmp1][tmp2].type == 3 && array[tmp1][tmp2].activity == 0) {
			printf("the vent is closed.\n");
		}
		else if (array[tmp1][tmp2].type == 3 && array[tmp1][tmp2].activity == 1) {
			printf("going to which one? it can be perceived by x & y:\n");
			int x;
			int y;
			scanf_s("%d %d", &x, &y);
			bool done = 0;
			if (x == 6 && y == 13) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 817;
					dest->y = 365;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 4 && y == 1) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 165;
					dest->y = 240;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 4 && y == 6) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 436;
					dest->y = 270;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 1 && y == 6) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 436;
					dest->y = 85;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 6 && y == 8) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 545;
					dest->y = 395;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 9 && y == 8) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 545;
					dest->y = 580;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 8 && y == 3) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 272;
					dest->y = 488;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 2 && y == 12) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 760;
					dest->y = 148;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
		}
	}
}


void SH_Ability(characters** list,SDL_Texture** IL_tex, SDL_Texture* IL2_tex, SDL_Texture** MS_tex, SDL_Texture* MS2_tex, SDL_Texture** SH_tex, SDL_Texture* SH2_tex, SDL_Texture** JS_tex, SDL_Texture* JS2_tex, SDL_Texture** JW_tex, SDL_Texture* JW2_tex, SDL_Texture** SG_tex, SDL_Texture* SG2_tex, SDL_Texture** WG_tex, SDL_Texture* WG2_tex, SDL_Texture** JB_tex, SDL_Texture* JB2_tex, char first, char second) {
	srand(time(0));
	bool finish = 0;
	while (finish == 0) {
		int random = rand() % 8 + 1;

		characters* tmp = *list;
		for (int i = 0; i < random - 1; i++) {
			tmp = tmp->next;
		}

		char name[3];
		name[2] = '\0';
		name[0] = tmp->name[0];
		name[1] = tmp->name[1];

		if (strcmp(name, "IL") == 0 && !(name[0] == first && name[1] == second)) {
			*IL_tex = IL2_tex;
			finish = 1;
		}
		else if (strcmp(name, "MS") == 0 && !(name[0] == first && name[1] == second)) {
			*MS_tex = MS2_tex;
			finish = 1;
		}
		else if (strcmp(name, "SH") == 0 && !(name[0] == first && name[1] == second)) {
			*SH_tex = SH2_tex;
			finish = 1;
		}
		else if (strcmp(name, "JS") == 0 && !(name[0] == first && name[1] == second)) {
			*JS_tex = JS2_tex;
			finish = 1;
		}
		else if (strcmp(name, "SG") == 0 && !(name[0] == first && name[1] == second)) {
			*SG_tex = SG2_tex;
			finish = 1;
		}
		else if (strcmp(name, "WG") == 0 && !(name[0] == first && name[1] == second)) {
			*WG_tex = WG2_tex;
			finish = 1;
		}
		else if (strcmp(name, "JB") == 0 && !(name[0] == first && name[1] == second)) {
			*JB_tex = JB2_tex;
			finish = 1;
		}
		else if (strcmp(name, "JB") == 0 && !(name[0] == first && name[1] == second)) {
			*JW_tex = JW2_tex;
			finish = 1;
		}
	}
}

void WG_Ability(SDL_Rect* dest1, SDL_Rect* dest2) {
	int x = dest2->x;
	dest2->x = dest1->x;
	dest1->x = x;
	int y = dest2->y;
	dest2->y = dest1->y;
	dest1->y = y;
}


int IL_Ability(int i, int j, int i2, int j2,room array[9][13],SDL_Rect* ban,SDL_Rect* ban2,SDL_Rect* ban3,SDL_Rect* ban4,SDL_Rect* final1,SDL_Rect* final2) {
	SDL_Rect* tmp = NULL;

	if (i == 2 && j == 2) {
		tmp = ban4;
	}
	else if (i == 2 && j == 12) {
		tmp = ban;
	}
	else if (i == 8 && j == 2) {
		tmp = ban2;
	}
	else if (i == 8 && j == 12) {
		tmp = ban3;
	}
	else {
		return -1;
	}
	SDL_Rect* tmp2 = NULL;
	if (i2 == 2 && j2 == 2) {
		tmp2 = ban4;
	}
	else if (i2 == 2 && j2 == 12) {
		tmp2 = ban;
	}
	else if (i2 == 8 && j2 == 2) {
		tmp2 = ban2;
	}
	else if (i2 == 8 && j2 == 12) {
		tmp2 = ban3;
	}
	else {
		return -1;
	}
	
	if (tmp->x == final1->x && tmp->y == final1->y) {
		final1->x = tmp2->x;
		final1->y = tmp2->y;
		array[i - 1][j - 1].escape = 1;
		array[i2 - 1][j2 - 1].escape = 0;
	}
	else if (tmp->x == final2->x && tmp->y == final2->y) {
		final2->x = tmp2->x;
		final2->y = tmp2->y;
		array[i - 1][j - 1].escape = 1;
		array[i2 - 1][j2 - 1].escape = 0;
	}

	


	if (tmp == NULL || tmp2 == NULL) {
		return -1;
	}
	else {
		return 0;
	}



}

int JS_Ability(int i, int j, int i2, int j2, room array[9][13], SDL_Rect* light1, SDL_Rect* light2, SDL_Rect* light3, SDL_Rect* light4, SDL_Rect* light_1, SDL_Rect* light_2, SDL_Rect* tmp1, SDL_Rect* tmp2, SDL_Rect* tmp3, SDL_Rect* tmp4, SDL_Rect* tmp_1, SDL_Rect* tmp_2) {
	SDL_Rect* first = NULL;
	if (i == 7 && j == 2) {
		first = light1;
	}
	else if (i == 3 && j == 12) {
		first = light2;
	}
	else if (i == 3 && j == 3) {
		first = light3;
	}
	else if (i == 8 && j == 11) {
		first = light4;
	}
	else if (i == 6 && j == 6) {
		first = light_1;
	}
	else if (i == 5 && j == 8) {
		first = light_2;
	}
	else if (i == 2 && j == 6) {
		SDL_Rect* x = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		x->x = 437;
		x->y = 149;
		first = x;
	}
	else if (i == 8 && j == 8) {
		SDL_Rect* x = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		x->x = 545;
		x->y = 517;
		first = x;
	}
	SDL_Rect* second = NULL;
	
	if (i2 == 7 && j2 == 2) {
		second = light1;
	}
	else if (i2 == 3 && j2 == 12) {
		second = light2;
	}
	else if (i2 == 3 && j2 == 3) {
		second = light3;
	}
	else if (i2 == 8 && j2 == 11) {
		second = light4;
	}
	else if (i2 == 6 && j2 == 6) {
		second = light_1;
	}
	else if (i2 == 5 && j2 == 8) {
		second = light_2;
	}
	else if (i2 == 2 && j2 == 6) {
		SDL_Rect* x = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		x->x = 437;
		x->y = 149;
		second = x;
	}
	else if (i2 == 8 && j2 == 8) {
		SDL_Rect* x = (SDL_Rect*) calloc(1,sizeof(SDL_Rect));
		x->x = 545;
		x->y = 517;
		second = x;
	}
	if (first->x = tmp1->x && first->y == tmp1->y) {
		tmp1->x = second->x;
		tmp1->y = second->y;
		array[i - 1][j - 1].activity = 0;
		array[i2 - 1][j2 - 1].activity = 1;
	}
	else if (first->x = tmp2->x && first->y == tmp2->y) {
		tmp2->x = second->x;
		tmp2->y = second->y;
		array[i - 1][j - 1].activity = 0;
		array[i2 - 1][j2 - 1].activity = 1;
	}
	else if (first->x = tmp3->x && first->y == tmp3->y) {
		tmp3->x = second->x;
		tmp3->y = second->y;
		array[i - 1][j - 1].activity = 0;
		array[i2 - 1][j2 - 1].activity = 1;
	}
	else if (first->x = tmp4->x && first->y == tmp4->y) {
		tmp4->x = second->x;
		tmp4->y = second->y;
		array[i - 1][j - 1].activity = 0;
		array[i2 - 1][j2 - 1].activity = 1;
	}
	else if (first->x = tmp_1->x && first->y == tmp_1->y) {
		tmp_1->x = second->x;
		tmp_1->y = second->y;
		array[i - 1][j - 1].activity = 0;
		array[i2 - 1][j2 - 1].activity = 1;
	}
	else if (first->x = tmp_2->x && first->y == tmp_2->y) {
		tmp_2->x = second->x;
		tmp_2->y = second->y;
		array[i - 1][j - 1].activity = 0;
		array[i2 - 1][j2 - 1].activity = 1;
	}

	if (first == NULL || second == NULL) {
		return -1;
	}
	else {
		return 0;
	}

	


}

void MS_Ability(room array[9][13], char name[3], SDL_Rect* dest, int* i, int first, int second) {
	int tmp1;
	int tmp2;


	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (strcmp(name, array[i][j].name) == 0) {
				tmp1 = i;
				tmp2 = j;
			}
		}
	}

	printf("OK, now where you wanna go/do by this character?\n\n");

	printf("WARNING : remember, you have only 3 chances to make your move : \n");
	printf("HINT : to go up , press 'W'.\n ");
	printf("to go down , press 'S'. \n ");
	printf(" to go left down , press 'SA'. \n");
	printf(" to go left up , press 'WA'. \n");
	printf(" to go right up , press 'WD'. \n");
	printf("to go right down , press 'SD'. \n\n");
	printf("to use vent, press 'V' :\n");
	printf("Whenever your choice is done , hit enter to continue. \n");
	printf("you can stop moving by pressing 'C':\n");



	char move[3];



	gets(move);

	if (*i > 1 && strcmp(move, "C") == 0) {
		if (array[tmp1][tmp2].type != 1);
		*i = 4;
		return;
	}
	else if (*i == 1 && strcmp(move, "C") == 0) {
		printf("you have to move at least 1 hex.\n");
	}

	if (tmp2 % 2 == 1) {
		if (strcmp(move, "WA") == 0 && tmp2 - 1 >= 0) {
			if (array[tmp1][tmp2 - 1].type != 4 && !(array[tmp1][tmp2 - 1].name[0] != 'N') && !(tmp1 == first && tmp2 - 1 == second) && !(array[tmp1][tmp2 - 1].type == 1 && *i == 4)) {
				array[tmp1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x -= 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "WD") == 0 && tmp2 + 1 <= 13) {
			if (array[tmp1][tmp2 + 1].type != 4 && !(array[tmp1][tmp2 + 1].name[0] != 'N') && !(tmp1 == first && tmp2 + 1 == second) && !(array[tmp1][tmp2 + 1].type == 1 && *i == 4)) {
				array[tmp1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x += 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "SA") == 0 && tmp2 - 1 >= 0 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2 - 1].type != 4 && !(array[tmp1 + 1][tmp2 - 1].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 - 1 == second) && !(array[tmp1 + 1][tmp2 - 1].type == 1 && *i == 4)) {
				array[tmp1 + 1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 30;
				dest->x -= 55;
				(*i)++;
			}
		}
		else if (strcmp(move, "SD") == 0 && tmp2 + 1 <= 13 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2 + 1].type != 4 && !(array[tmp1 + 1][tmp2 + 1].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 + 1 == second) && !(array[tmp1 + 1][tmp2 + 1].type == 1 && *i == 4)) {
				array[tmp1 + 1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 30;
				dest->x += 55;
				(*i)++;
			}
		}
		else if (strcmp(move, "S") == 0 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2].type != 4 && !(array[tmp1 + 1][tmp2].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 == second) && !(array[tmp1 + 1][tmp2].type == 1 && *i == 4)) {
				array[tmp1 + 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 61;
				(*i)++;
			}
		}
		else if (strcmp(move, "W") == 0 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2].type != 4 && !(array[tmp1 - 1][tmp2].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 == second) && !(array[tmp1 - 1][tmp2].type == 1 && *i == 4)) {
				array[tmp1 - 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y -= 61;
				(*i)++;
			}
		}
	}

	else {
		if (strcmp(move, "WA") == 0 && tmp2 - 1 >= 0 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2 - 1].type != 4 && !(array[tmp1 - 1][tmp2 - 1].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 - 1 == second) && !(array[tmp1 - 1][tmp2 - 1].type == 1 && *i == 4)) {
				array[tmp1 - 1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x -= 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "WD") == 0 && tmp2 + 1 <= 13 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2 + 1].type != 4 && !(array[tmp1 - 1][tmp2 + 1].name[0] != 'N') && !(tmp1 - 1 == first && tmp2 + 1 == second) && !(array[tmp1 - 1][tmp2 + 1].type == 1 && *i == 4)) {
				array[tmp1 - 1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x += 55;
				dest->y -= 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "SA") == 0 && tmp2 - 1 >= 0) {
			if (array[tmp1][tmp2 - 1].type != 4 && !(array[tmp1][tmp2 - 1].name[0] != 'N') && !(tmp1 == first && tmp2 - 1 == second) && !(array[tmp1][tmp2 - 1].type == 1 && *i == 4)) {
				array[tmp1][tmp2 - 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 - 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x -= 55;
				dest->y += 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "SD") == 0 && tmp2 + 1 <= 13) {
			if (array[tmp1][tmp2 + 1].type != 4 && !(array[tmp1][tmp2 + 1].name[0] != 'N') && !(tmp1 == first && tmp2 + 1 == second) && !(array[tmp1][tmp2 + 1].type == 1 && *i == 4)) {
				array[tmp1][tmp2 + 1].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1][tmp2 + 1].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->x += 55;
				dest->y += 30;
				(*i)++;
			}
		}
		else if (strcmp(move, "S") == 0 && tmp1 + 1 <= 9) {
			if (array[tmp1 + 1][tmp2].type != 4 && !(array[tmp1 + 1][tmp2].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 == second) && !(array[tmp1 + 1][tmp2].type == 1 && *i == 4)) {
				array[tmp1 + 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 + 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y += 61;
				(*i)++;
			}
		}
		else if (strcmp(move, "W") == 0 && tmp1 - 1 >= 0) {
			if (array[tmp1 - 1][tmp2].type != 4 && !(array[tmp1 - 1][tmp2].name[0] != 'N') && !(tmp1 + 1 == first && tmp2 == second) && !(array[tmp1 + 1][tmp2].type == 1 && *i == 4)) {
				array[tmp1 - 1][tmp2].name[0] = array[tmp1][tmp2].name[0];
				array[tmp1 - 1][tmp2].name[1] = array[tmp1][tmp2].name[1];
				array[tmp1][tmp2].name[0] = 'N';
				array[tmp1][tmp2].name[1] = 'O';
				dest->y -= 61;
				(*i)++;
			}
		}
	}

	if (strcmp(move, "V") == 0) {
		if (array[tmp1][tmp2].type == 3 && array[tmp1][tmp2].activity == 0) {
			printf("the vent is closed.\n");
		}
		else if (array[tmp1][tmp2].type == 3 && array[tmp1][tmp2].activity == 1) {
			printf("going to which one? it can be perceived by x & y:\n");
			int x;
			int y;
			scanf_s("%d %d", &x, &y);
			bool done = 0;
			if (x == 6 && y == 13) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 817;
					dest->y = 365;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 4 && y == 1) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 165;
					dest->y = 240;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 4 && y == 6) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 436;
					dest->y = 270;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 1 && y == 6) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 436;
					dest->y = 85;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 6 && y == 8) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 545;
					dest->y = 395;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 9 && y == 8) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 545;
					dest->y = 580;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 8 && y == 3) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 272;
					dest->y = 488;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
			else if (x == 2 && y == 12) {
				if (!(array[x - 1][y - 1].name[0] != 'N') && array[x - 1][y - 1].activity == 1) {
					dest->x = 760;
					dest->y = 148;
					array[x - 1][y - 1].name[0] = array[tmp1][tmp2].name[0];
					array[x - 1][y - 1].name[1] = array[tmp1][tmp2].name[1];
					array[x - 1][y - 1].name[2] = array[tmp1][tmp2].name[2];
					array[tmp1][tmp2].name[0] = 'N';
					array[tmp1][tmp2].name[1] = 'O';
					array[tmp1][tmp2].name[2] = '\0';
					(*i)++;
				}
			}
		}
	}
}


int JB_Ability(int i, int j, int i2, int j2,room array[9][13],SDL_Rect* tmp1, SDL_Rect* tmp2) {
	SDL_Rect* final1 = NULL;
	SDL_Rect* final2 = NULL;
	if (i == 6 && j == 13) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 817;
		final1->y = 365;
	}
	else if (i == 4 && j == 1) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 165;
		final1->y = 240;
	}
	else if (i == 4 && j == 6) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 436;
		final1->y = 270;
	}
	else if (i == 1 && j == 6) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 436;
		final1->y = 85;
	}
	else if (i == 6 && j == 8) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 545;
		final1->y = 395;
	}
	else if (i == 9 && j == 8) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 545;
		final1->y = 580;
	}
	else if (i == 8 && j == 3) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 272;
		final1->y = 488;
	}
	else if (i == 2 && j == 12) {
		final1 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final1->x = 760;
		final1->y = 148;
	}

	if (i2 == 6 && j2 == 13) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 817;
		final2->y = 365;
	}
	else if (i2 == 4 && j2 == 1) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 165;
		final2->y = 240;
	}
	else if (i2 == 4 && j2 == 6) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 436;
		final2->y = 270;
	}
	else if (i2 == 1 && j2 == 6) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 436;
		final2->y = 85;
	}
	else if (i2 == 6 && j2 == 8) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 545;
		final2->y = 395;
	}
	else if (i2 == 9 && j2 == 8) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 545;
		final2->y = 580;
	}
	else if (i2 == 8 && j2 == 3) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 272;
		final2->y = 488;
	}
	else if (i2 == 2 && j2 == 12) {
		final2 = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
		final2->x = 760;
		final2->y = 148;
	}

	if (final1->x == tmp1->x && final1->y == tmp1->y) {
		tmp1->x = final2->x;
		tmp1->y = final2->y;
		array[i - 1][j - 1].activity = 1;
		array[i2 - 1][j2 - 1].activity = 0;
	}
	else if (final1->x == tmp2->x && final1->y == tmp2->y) {
		tmp2->x = final2->x;
		tmp2->y = final2->y;
		array[i - 1][j - 1].activity = 1;
		array[i2 - 1][j2 - 1].activity = 0;
	}

	if (final1 == NULL || final2 == NULL) {
		return -1;
	}
	else {
		return 0;
	}

}

void visiblity_checker(room array[9][13], char first, char second, SDL_Texture** IL, SDL_Texture** MS, SDL_Texture** SH, SDL_Texture** JW, SDL_Texture** JS, SDL_Texture** JB, SDL_Texture** SG, SDL_Texture** WG, SDL_Texture* IL2, SDL_Texture* MS2, SDL_Texture* SG2, SDL_Texture* JB2, SDL_Texture* JS2, SDL_Texture* JW2, SDL_Texture* WG2, SDL_Texture* SH2) {
	int visible;
	printf("is A %c",first);
	printf("is B %c", second);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (array[i][j].name[0] == first && array[i][j].name[1] == second) {
				visible = array[i][j].visiblity;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (strcmp(array[i][j].name, "IL") == 0) {
				if(array[i][j].visiblity != visible){
					*IL = IL2;
				}
			}
			if (strcmp(array[i][j].name, "MS") == 0) {
		    if (array[i][j].visiblity != visible) {
					*MS = MS2;
				}
			}
			if (strcmp(array[i][j].name, "SG") == 0) {
	        if (array[i][j].visiblity != visible) {
					*SG = SG2;
				 }
			}
			if (strcmp(array[i][j].name, "WG") == 0) {
		    if (array[i][j].visiblity != visible) {
					*WG = WG2;
				 }
			}
			if (strcmp(array[i][j].name, "SH") == 0) {
				if (array[i][j].visiblity != visible) {
					*SH = SH2;
				}
			}
			if (strcmp(array[i][j].name, "JW") == 0) {
				printf("%d", array[i][j].visiblity);
				if (array[i][j].visiblity != visible) {
					*JW = JW2;
				}
			}
			if (strcmp(array[i][j].name, "JS") == 0) {
				if (array[i][j].visiblity != visible) {
					*JS = JS2;
				}
			}
			if (strcmp(array[i][j].name, "JB") == 0) {
				if (array[i][j].visiblity != visible) {
					*JB = JB2;
				}
			}
		}
	}


}

void etmam(char name[3], room array[9][13],char final[3]) {
	int x = -1;
	int y = -1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 13; j++) {
			if (strcmp(array[i][j].name, name) == 0) {
				x = i;
				y = j;
			}
		}
	}
	if (x >= 0 && y >= 0) {
		printf("you can catch mr jack if you think he is next to you");
		if (y % 2 == 1) {
			if (y - 1 >= 0) {
				if (array[x][y - 1].name[0] != 'N') {
					printf("%s\n", array[x][y - 1].name);
				}
			}
			if (y - 1 >= 0 && x + 1 <= 8) {
				if (array[x + 1][y - 1].name[0] != 'N') {
					printf("%s\n", array[x + 1][y - 1].name);
				}
			}
			if (x + 1 <= 8) {
				if (array[x + 1][y].name[0] != 'N') {
					printf("%s\n", array[x + 1][y].name);
				}
			}
			if (x - 1 >= 0) {
				if (array[x - 1][y].name[0] != 'N') {
					printf("%s\n", array[x - 1][y].name);
				}
			}
			if (x + 1 <= 8 && y + 1 <= 12) {
				if (array[x + 1][y + 1].name[0] != 'N') {
					printf("%s\n", array[x + 1][y + 1].name);
				}
			}
			if (y + 1 <= 12) {
				if (array[x][y + 1].name[0] != 'N') {
					printf("%s\n", array[x][y + 1].name);
				}
			}
		}
		else {
			if (y - 1 >= 0 && x-1>= 0) {
				if (array[x][y - 1].name[0] != 'N') {
					printf("%s\n", array[x-1][y - 1].name);
				}
			}
			if (y - 1 >= 0) {
				if (array[x + 1][y - 1].name[0] != 'N') {
					printf("%s\n", array[x][y - 1].name);
				}
			}
			if (x + 1 <= 8) {
				if (array[x + 1][y].name[0] != 'N') {
					printf("%s\n", array[x + 1][y].name);
				}
			}
			if (x - 1 >= 0) {
				if (array[x - 1][y].name[0] != 'N') {
					printf("%s\n", array[x - 1][y].name);
				}
			}
			if (y + 1 <= 12) {
				if (array[x][y + 1].name[0] != 'N') {
					printf("%s\n", array[x][y + 1].name);
				}
			}
			if (y + 1 <= 12 && x-1>= 0) {
				if (array[x-1][y + 1].name[0] != 'N') {
					printf("%s\n", array[x-1][y + 1].name);
				}
			}
		}
	}

	gets(final);

}
