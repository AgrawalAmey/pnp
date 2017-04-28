#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

void render_scoreboard(SDL_Surface * screen, SDL_Surface * scoreboard){

	apply_surface( 640, 0, scoreboard, screen);

}