#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

void render_battle(char * user1, char * user2, char * poke1, char * poke2, SDL_Surface * battle, SDL_Surface * screen, TTF_Font * font){
	printf("%s\n", poke1);
	// SDL_Surface * pokeImg1 = NULL, * pokeImg2 = NULL;
	// pokeImg1 = load_image(strcat("../data/thm/", poke1));
	// pokeImg2 = load_image("");
	apply_surface(0, 0, battle, screen);

}