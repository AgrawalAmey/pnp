#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../login/login.h"

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Event event;
TTF_Font * font = NULL;
SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

struct stringInput{
	char str[20];
	SDL_Surface * text;
};

SDL_Surface * load_image( char * filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface * loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface * optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename );

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void append(char* s, char c)
{
        s[strlen(s)] = c;
        s[strlen(s)+1] = '\0';
}

void handle_input( struct stringInput * name )
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {

        //Keep a copy of the current version of the string
        char temp[20] = {'\0'};
        strcpy(temp, name->str);
        // printf("%s %d %c %s\n", temp, strlen(name->str),event.key.keysym.unicode, SDL_GetKeyName( event.key.keysym.sym));

        //If the string less than maximum size
        if( strlen(name->str) < 20 )
        {
            //If the key is a space
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                append( name->str,(char)event.key.keysym.unicode );
            }
            //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                append( name->str,(char)event.key.keysym.unicode );
                // printf("entered here %s\n", name->str);
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                append( name->str,(char)event.key.keysym.unicode );
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                append( name->str,(char)event.key.keysym.unicode );
            }
        }

        // //If backspace was pressed and the string isn't blank
        // // if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        // // {
        //     //Remove a character from the end
        //     // str.erase( str.length() - 1 );
        // // }

        //If the string was changed
        if( strcmp( name->str,temp) != 0 )
        {
            //Free the old surface
            SDL_FreeSurface( name->text );

            //Render a new text surface
            name->text = TTF_RenderText_Solid( font, name->str, textColor );
        }
    }
}

int main(int argc, char const *argv[])
{
	int quit = 0;

	SDL_Surface * welcome = NULL;
	SDL_Surface * screen = NULL;
	SDL_Surface *message1 = NULL;
	SDL_Surface *message2 = NULL;
	SDL_Surface *message3 = NULL;
	// SDL_Event event;
	// TTF_Font * font = NULL;
	// SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	struct stringInput * name = (struct stringInput *) malloc (sizeof(struct stringInput));
	name->text == NULL;
	memset(name->str,'\0',20);
	int nameEntered = 0;


	struct stringInput * pwd = (struct stringInput *) malloc (sizeof(struct stringInput));
	pwd->text == NULL;
	memset(pwd->str,'\0',20);
	int pwdEntered = 1;

	//start SDL
	SDL_Init (SDL_INIT_EVERYTHING);
	TTF_Init();
	//set up screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	//Set the window caption
    SDL_WM_SetCaption( "Welcome to Pokemon MMORPG", NULL );

    font = TTF_OpenFont( "./../../../data/GUI/fontb.ttf", 40 );
	welcome = load_image( "./../../../data/GUI/pokelogo.bmp" );
	
	message1 = TTF_RenderText_Solid( font, "Welcome to Pokemon MMORPG !!!", textColor );
	
	message2 = TTF_RenderText_Solid( font, "Enter your username:", textColor );

	//update Screen
	SDL_Flip(screen);

	//While the user hasn't quit
    while( quit == 0 )
    {
        //While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
        	SDL_EnableUNICODE(1);
        	
        	// if( 1 != 1)
        	if( pwdEntered == 0 && nameEntered == 1)
            {
                //Get user input
                handle_input(pwd);
                //If the enter key was pressed
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    pwdEntered == 1;
                    SDL_FreeSurface(pwd->text);
                    pwd->text = NULL;
                    SDL_FreeSurface( message2 );
                    //Change the message
                    message2 = TTF_RenderText_Solid( font, "Connecting to the serever...", textColor );
                }
            }


        	if( nameEntered == 0 )
            {
                //Get user input
                handle_input(name);
                //If the enter key was pressed
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    //Change the flag
                    nameEntered = 1;
                    pwdEntered = 0;
                    SDL_FreeSurface(name->text);
                    name->text = NULL;
                    //Free the old message surface
                    SDL_FreeSurface( message2 );
                    //Change the message
                    message2 = TTF_RenderText_Solid( font, "Enter your password:", textColor );
                }
            }

            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = 1;
            }
        }

        apply_surface( 0, 0, welcome, screen );
        apply_surface( ( SCREEN_WIDTH - message1->w ) / 2, ( ( SCREEN_HEIGHT / 3 ) - message1->h ) / 2, message1, screen );
        apply_surface( ( SCREEN_WIDTH - message2->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - message2->h ) / 2, message2, screen );
        if( name->text != NULL )
	    {
	        //Show the name
	        apply_surface( ( SCREEN_WIDTH - (name->text)->w ) / 2, ( SCREEN_HEIGHT - (name->text)->h ) / 2, name->text, screen );
	    }
	    if( pwd->text != NULL )
	    {
	        //Show the name
	        apply_surface( ( SCREEN_WIDTH - (pwd->text)->w ) / 2, ( SCREEN_HEIGHT - (pwd->text)->h ) / 2, pwd->text, screen );
	    }
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

    }

	//free the loaded image
	SDL_FreeSurface (welcome);
    SDL_FreeSurface( message1 );
    SDL_FreeSurface( message2 );
    SDL_FreeSurface( message3 );

    //Close the font that was used
    TTF_CloseFont( font );

    TTF_Quit();
	SDL_Quit();
	return 0;
}