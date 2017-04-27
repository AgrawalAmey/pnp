#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

void render_players(struct hashTable * hashtable, SDL_Surface * screen, SDL_Surface * sprite, int xOffset, int yOffset, TTF_Font * font){
	int i = 0;
	for(i=0;i<hashtable->size;i++){
		if (hashtable->list[i].username[i] == '\0')
		{
			continue;
		}

		SDL_Surface * showName = NULL;
		SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

		showName = TTF_RenderText_Solid(font, hashtable->list[i].username, textColor);

		// printf("%s\n", hashtable->list[i].username);

		SDL_Rect playerPosition;
		playerPosition.x = xOffset + hashtable->list[i].x;
		playerPosition.y = yOffset + hashtable->list[i].y;

		SDL_Rect spriteFrame;
		spriteFrame.x = 0;
		spriteFrame.y = 0;
		spriteFrame.w = 64;
    	spriteFrame.h = 64;

		SDL_BlitSurface(sprite, &spriteFrame, screen, &playerPosition);
		apply_surface( playerPosition.x + ( 64 - showName->w )/2, playerPosition.y - 20, showName, screen);

		SDL_FreeSurface(showName);
	}
}