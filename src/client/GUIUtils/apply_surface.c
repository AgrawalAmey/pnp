#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

//apply_surface takes the destination surface and renders it
//to the source at coordinates x and y
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface(source, NULL, destination, &offset);
}