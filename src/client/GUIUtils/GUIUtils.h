// Definations for all util functions
#ifndef GUIUTILS
#define GUIUTILS

//this function return a optimized version of a image after loading it
SDL_Surface * load_image(char * filename);

//this function appends a character to a string s
void append(char* s, char c);

//the destination surface is rendered in memory to the source at coordinates x and y
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

//this function is resposible for the typing screen during password
void handle_input(struct stringInput * name, SDL_Event event, TTF_Font * font, SDL_Color textColor);

//this function is responsible for rendering background during game
void render_background(int x, int y, SDL_Surface* source, SDL_Surface* destination);

void initializeSHM(struct hashTable * hashtable);

#endif // GUIUTILS
