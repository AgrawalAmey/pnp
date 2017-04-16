#include "./includeGUI.h"
#include "./GUIUtils.h"

//this function return a optimized version of a image after loading it
SDL_Surface * load_image(char * filename)
{
    //Temporary storage for the image that's loaded
    SDL_Surface * loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface * optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename);

    //If nothing went wrong in loading the image
    if(loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);
        //Free the old image
        SDL_FreeSurface(loadedImage);
    }
    else
    {
        //error handling if the image wasnt loaded
    	printf("Error in function load_image....Exiting!\n");
    	exit(1);
    }

    //Return the optimized image
    return optimizedImage;
}