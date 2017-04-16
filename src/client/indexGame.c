#include "./GUIUtils/includeGUI.h"
#include "./GUIUtils/GUIUtils.h"
#include "./login/login.h"

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int SPRITE_SIZE = 32;


/* source and destination rectangles */
SDL_Rect rcSrc, rcSprite;
int xGlobal, yGlobal;
int gameover = 0;

void HandleEvent(SDL_Event event)
{
    switch (event.type) {
        /* close button clicked */
        case SDL_QUIT:
            gameover = 1;
            break;
            
        /* handle the keyboard */
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    gameover = 1;
                    break;
                case SDLK_LEFT:
                    if ( rcSrc.x == 192 )
                        rcSrc.x = 224;
                    else
                        rcSrc.x = 192;
                    rcSprite.x -= 5;
                    if (xGlobal - rcSprite.x >= 160)
                    {
                        xGlobal = xGlobal - 160 + rcSprite.x;
                    }
                    break;
                case SDLK_RIGHT:
                    if ( rcSrc.x == 64 )
                        rcSrc.x = 96;
                    else
                        rcSrc.x = 64;
                    rcSprite.x += 5;
                    if (rcSprite.x - xGlobal >= 160)
                    {
                        xGlobal = xGlobal - 480 + rcSprite.x;
                    }
                    break;
                case SDLK_UP:
                    if ( rcSrc.x == 0 )
                        rcSrc.x = 32;
                    else
                        rcSrc.x = 0;
                    rcSprite.y -= 5;
                    break;
                case SDLK_DOWN:
                    if ( rcSrc.x == 128 )
                        rcSrc.x = 160;
                    else
                        rcSrc.x = 128;
                    rcSprite.y += 5;
                    break;
            }
            break;
    }
}
// SDL_Event event;
// TTF_Font * font = NULL;
// SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

struct clientInfo{

};

// struct background{
//     int xl, yl, xh, yh; //rectangular coordinates of the are
//     int texture; //texture number 1 default
// };

//the main loop on the client side
//handles all the keyboard event
int main(int argc, char const *argv[])
{
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                      declarations of SDL elements
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    SDL_Surface * screen = NULL,* welcomeImage = NULL;
    SDL_Surface * message1 = NULL, * message2 = NULL, * message3 = NULL;
    SDL_Event event;
    TTF_Font * font = NULL;
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    Mix_Music * music = NULL;


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                      initializing SDL
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    SDL_WM_SetCaption( "Welcome to Pokemon MMORPG", NULL );


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                      loading music
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        printf("Error initializing music stream...Exiting!!\n");
        exit(1);
    }
    music = Mix_LoadMUS("./../src/client/GUIGraphics/opening.wav");
    if(music == NULL)
    {
        printf("Error loading music...Exiting!!\n");
        exit(1);
    }
    if( Mix_PlayMusic( music, -1 ) == -1 )
    {
        printf("Error in playing music...Exiting!!\n");
        exit(1);
    }


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                      declaration of name and passwords
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    struct stringInput * name = (struct stringInput *) malloc (sizeof(struct stringInput));
    name->text == NULL;
    memset(name->str,'\0',20);
    int nameEntered = 0;

    struct stringInput * pwd = (struct stringInput *) malloc (sizeof(struct stringInput));
    pwd->text == NULL;
    memset(pwd->str,'\0',20);
    int pwdEntered = 1;
    

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                loading files
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    font = TTF_OpenFont("./../src/client/GUIGraphics/fontb.ttf", 40);
    welcomeImage = load_image("./../src/client/GUIGraphics/pokelogo.bmp");
    if (font == NULL || welcomeImage == NULL)
    {
        printf("Error loading files....Exiting!!\n");
        exit(1);
    }

    message1 = TTF_RenderText_Solid( font, "Welcome to Pokemon MMORPG !!!", textColor );
    message2 = TTF_RenderText_Solid( font, "Enter your username:", textColor );

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                flag variales
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    int loginReturn;
    int quitLoginLoop = 0;

    char result[1000]= {'\0'};
    char displayResult[100] = {'\0'};


    while( quitLoginLoop == 0 )
    {
        while(SDL_PollEvent(&event))
        {
            SDL_EnableUNICODE(1);
            if(pwdEntered == 0 && nameEntered == 1)
            {
                handle_input(pwd, event, font, textColor);
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    pwdEntered == 1;
                    SDL_FreeSurface(pwd->text);
                    pwd->text = NULL;
                    SDL_FreeSurface( message2 );
                    message2 = TTF_RenderText_Solid( font, "Connecting to the serever...", textColor );
                    login(result, "login", "name", name->str, pwd->str);
                    printf("%s\n", result);
                    if (result[0] == 's')
                    {
                        loginReturn = 1;
                        strcpy(displayResult, "Logged in succesfully!");
                    }
                    else
                    {
                        loginReturn = 0;
                        strcpy(displayResult, "Username and/or password Incorrect. Please try again!");
                    }
                    font = TTF_OpenFont("./../src/client/GUIGraphics/fontb.ttf", 20);
                    message3 = TTF_RenderText_Solid( font, displayResult, textColor);
                    quitLoginLoop = 1;
                }
            }
            if( nameEntered == 0 )
            {
                //Get user input
                handle_input(name, event, font, textColor);
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

            if( event.type == SDL_QUIT )
            {
                exit(1);
            }
        }

        apply_surface( 0, 0, welcomeImage, screen );
        apply_surface( ( SCREEN_WIDTH - message1->w ) / 2, ( ( SCREEN_HEIGHT / 3 ) - message1->h ) / 2, message1, screen );
        apply_surface( ( SCREEN_WIDTH - message2->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - message2->h ) / 2, message2, screen );
        if( message3 != NULL )
            apply_surface( ( SCREEN_WIDTH - message3->w ) / 2, ( ( SCREEN_HEIGHT  ) - message3->h ) / 2, message3, screen );

        if( name->text != NULL )
            apply_surface( ( SCREEN_WIDTH - (name->text)->w ) / 2, ( SCREEN_HEIGHT - (name->text)->h ) / 2, name->text, screen );

        if( pwd->text != NULL )
            apply_surface( ( SCREEN_WIDTH - (pwd->text)->w ) / 2, ( SCREEN_HEIGHT - (pwd->text)->h ) / 2, pwd->text, screen );

        if( SDL_Flip( screen ) == -1 )
        {
            printf("Error in updating screen...Exiting!!\n");
            exit(1);
        }

    }

    if (loginReturn == 0)
    {
        sleep(4);
        SDL_FreeSurface(welcomeImage);
        SDL_FreeSurface(message1);
        SDL_FreeSurface(message2);
        SDL_FreeSurface(message3);
        Mix_FreeMusic(music);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
    //free the loaded image
    SDL_FreeSurface (welcomeImage);
    SDL_FreeSurface( message1 );
    SDL_FreeSurface( message2 );
    SDL_FreeSurface( message3 );
    //Close the font that was used
    TTF_CloseFont( font );

    printf("now I have to implement game graphics.\n");

    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    SDL_Surface * game = load_image("./../src/client/GUIGraphics/game.jpg");
    SDL_Surface * sprite = load_image("./../src/client/GUIGraphics/sprite.bmp");
    int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);



    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    SDL_WM_SetCaption( "Start your quest in Pokemon MMORPG", NULL );
    SDL_EnableKeyRepeat(70, 70);

    int x = 320, y = 240;

    //get x y

    xGlobal = x;
    yGlobal = y;
    apply_surface(xGlobal-(SCREEN_WIDTH/2),yGlobal-(SCREEN_HEIGHT/2),game,screen);

    /* set sprite position */
    rcSprite.x = x;
    rcSprite.y = y;

    /* set animation frame */
    rcSrc.x = 128;
    rcSrc.y = 0;
    rcSrc.w = SPRITE_SIZE;
    rcSrc.h = SPRITE_SIZE;

    gameover = 0;

    /* message pump */
    while (!gameover)
    {
        SDL_Event event;
        
        /* look for an event */
        if (SDL_PollEvent(&event)) {
            HandleEvent(event);
        }

        /* collide with edges of screen */
        // if (rcSprite.x <= 0)
        //     rcSprite.x = 0;
        // if (rcSprite.x >= SCREEN_WIDTH - SPRITE_SIZE) 
        //     rcSprite.x = SCREEN_WIDTH - SPRITE_SIZE;

        // if (rcSprite.y <= 0)
        //     rcSprite.y = 0;
        // if (rcSprite.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
        //     rcSprite.y = SCREEN_HEIGHT - SPRITE_SIZE;

        /* draw the grass */
        // for (int x = 0; x < SCREEN_WIDTH / SPRITE_SIZE; x++) {
        //     for (int y = 0; y < SCREEN_HEIGHT / SPRITE_SIZE; y++) {
        //         rcGrass.x = x * SPRITE_SIZE;
        //         rcGrass.y = y * SPRITE_SIZE;
        //         SDL_BlitSurface(grass, NULL, screen, &rcGrass);
        //     }
        // }

        apply_surface(xGlobal-(SCREEN_WIDTH/2),yGlobal-(SCREEN_HEIGHT/2),game,screen);
        /* draw the sprite */
        SDL_BlitSurface(sprite, &rcSrc, screen, &rcSprite);

        /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }

    // pause();
    // SDL_FreeSurface(gameScreen);
    Mix_FreeMusic( music );
    TTF_Quit();
    SDL_Quit();

    return 0;
}