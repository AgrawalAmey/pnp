#include "./includeGUI.h"
#include "./GUIUtils.h"

void render_background(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	//Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    int i = 0;
    int j = 0;
    for(i=0;i<10;i++){
    	for(j=0;j<10;j++){
    		offset.x = x + i*640;
    		offset.y = y + j*480;

    		SDL_BlitSurface(source, NULL, destination, &offset);
    	}
    }
}