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

void render_players(struct hashTable * hashtable, SDL_Surface * screen, SDL_Surface * sprite, int xOffset, int yOffset, TTF_Font * font);

void render_scoreboard(SDL_Surface * screen, SDL_Surface * scoreboard);

void render_pokemons(char * buffer, SDL_Surface * screen);

void render_battle(char * user1, char * user2, char * poke1, char * poke2, SDL_Surface * battle, SDL_Surface * screen, TTF_Font * font);

#endif // GUIUTILS
