#include "../../utils/includes.h"
#include "./includeGUI.h"
#include "./GUIUtils.h"

//this function is resposible for the typing screen during password
void handle_input(struct stringInput * name, SDL_Event event, TTF_Font * font, SDL_Color textColor)
{
    //If a key was pressed down
    if(event.type == SDL_KEYDOWN)
    {
        //Keep a copy of the current version of the string
        char temp[20] = {'\0'};
        strcpy(temp, (name->str));

        //If the string less than maximum size
        if(strlen(name->str) < 20)
        {
            //If the key is a underscore
            if(event.key.keysym.unicode == (Uint16)'_')
            {
                //Append the character
                append(name->str,(char)event.key.keysym.unicode);
            }
            //If the key is a number
            else if((event.key.keysym.unicode >= (Uint16)'0') && ( event.key.keysym.unicode <= (Uint16)'9'))
            {
                //Append the character
                append(name->str,(char)event.key.keysym.unicode);
            }
            //If the key is a uppercase letter
            else if((event.key.keysym.unicode >= (Uint16)'A') && ( event.key.keysym.unicode <= (Uint16)'Z'))
            {
                //Append the character
                append(name->str,(char)event.key.keysym.unicode);
            }
            //If the key is a lowercase letter
            else if((event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z'))
            {
                //Append the character
                append(name->str,(char)event.key.keysym.unicode);
            }
        }

        //If backspace was pressed and the string isn't blank
        if((event.key.keysym.sym == SDLK_BACKSPACE) && (strlen(name->str) != 0))
        {
            //Remove a character from the end
            name->str[strlen(name->str)-1] = '\0';
        }

        //If the string was changed
        if( strcmp(name->str,temp) != 0)
        {
            //Free the old surface
            SDL_FreeSurface(name->text);
            //Render a new text surface
            name->text = TTF_RenderText_Solid(font, name->str, textColor);
        }
    }
}