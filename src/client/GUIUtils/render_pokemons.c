#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

void render_pokemons(char * buffer, SDL_Surface * screen){
	// char ** tokenList = strSplit(buffer, " ");
	// int n = atoi(tokenList[0]);
	int n = (buffer[0] - '0');
	printf("render pokemon no : %d\n", n);

	int i = 0;
	for(i;i<n;i++){
		SDL_Surface * pokemon = load_image("../data/thm/abra.png");
		apply_surface(20+100*i, 180, pokemon, screen);
	}
}