#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

void render_players(struct hashTable * hashtable, SDL_Surface * screen, SDL_Surface * sprite, int xOffset, int yOffset){
	int i = 0;
	for(i=0;i<hashtable->size;i++){
		if (hashtable->list[i].username[i] == '\0')
		{
			continue;
		}

		// printf("%s\n", hashtable->list[i].username);

		SDL_Rect playerPosition;
		playerPosition.x = xOffset + hashtable->list[i].x;
		playerPosition.y = yOffset + hashtable->list[i].y;

		SDL_Rect spriteFrame;
		spriteFrame.x = 128;
		spriteFrame.y = 0;
		spriteFrame.w = 32;
    	spriteFrame.h = 32;

		SDL_BlitSurface(sprite, &spriteFrame, screen, &playerPosition);
	}
}