#include "./GUIUtils/includeGUI.h"
#include "./GUIUtils/GUIUtils.h"
#include "./login/login.h"

//The attributes of the screen
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int SCREEN_BPP = 32;


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
    int pwdEntered = 0;


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
    int loginReturn = 0;
    int quitLoginLoop = 0;

    char result[1000]= {'\0'};
    char displayResult[100] = {'\0'};


    while( quitLoginLoop == 0 )
    {
        if(SDL_PollEvent(&event))
        {
            SDL_EnableUNICODE(1);
            if(pwdEntered == 0 && nameEntered == 1)
            {
                handle_input(pwd, event, font, textColor);
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    pwdEntered = 1;
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
            else if( nameEntered == 0 )
            {
                handle_input(name, event, font, textColor);
                if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN))
                {
                    nameEntered = 1;
                    pwdEntered = 0;
                    SDL_FreeSurface(name->text);
                    name->text = NULL;
                    SDL_FreeSurface( message2 );
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
        // sleep(4);
        SDL_FreeSurface(welcomeImage);
        SDL_FreeSurface(message1);
        SDL_FreeSurface(message2);
        SDL_FreeSurface(message3);
        Mix_FreeMusic(music);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        // exit(1);
        return 0;
    }

    SDL_FreeSurface(welcomeImage);
    SDL_FreeSurface(message1);
    SDL_FreeSurface(message2);
    SDL_FreeSurface(message3);
    TTF_CloseFont(font);
    
    printf("now I have to implement game graphics.\n");

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                 Setting up a shared memory
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    int shmid;
    struct hashTable * hashtable;
    if ((shmid = shmget(IPC_PRIVATE, sizeof(struct hashTable), 0666 | IPC_CREAT)) == -1){
            perror("shmget:");
            exit(1);
    }
    if ((hashtable = shmat(shmid, (void *) 0, 0)) == (struct hashTable *) (-1)){
            perror("shmat:");
            exit(1);
    }
    initializeSHM(hashtable);
    // printf("%s\n", hashtable->list[1].username);
    

    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                      declarations of SDL Game elements
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    SDL_Surface * gameImage = NULL, * sprite = NULL;
    SDL_Rect playerPosition, spriteFrame;
    int colorKey = SDL_MapRGB(screen->format, 255, 0, 255);
    int quitGameLoop = 0;
    
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                  Changing SDL window properties
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    SDL_WM_SetCaption("Start your quest in Pokemon MMORPG", NULL);
    SDL_EnableKeyRepeat(70, 70);
    
    
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                  loding images
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    gameImage = load_image("./../src/client/GUIGraphics/money.gif");
    sprite = load_image("./../src/client/GUIGraphics/sprite.bmp");
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorKey);
    
    
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                   Player location variables
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    int x = 320, y = 240;
    hashtable->myX = x;
    hashtable->myY = y;
    int xImageLeft = x - 320, yImageTop = y - 240;
    
    playerPosition.x = x - xImageLeft;
    playerPosition.y = y - yImageTop;
    
    spriteFrame.x = 128;
    spriteFrame.y = 0;
    spriteFrame.w = 32;
    spriteFrame.h = 32;


    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    //                  Forking for network handling child process
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    if (!fork())
    {
        //child process code
        udpGameClient(hashtable);
        exit(1);
    }
    
    /*
    while(quitGameLoop == 0){
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    if (spriteFrame.x == 64)
                    {
                        spriteFrame.x = 96;
                    }
                    else
                    {
                        spriteFrame.x = 64;
                    }
                    if (playerPosition.x >= 480)
                    {
                        xImageLeft -= 5;
                    }
                    else
                    {
                        playerPosition.x += 5;
                    }
                    printf("%d %d %d\n", playerPosition.x, playerPosition.x - xImageLeft, xImageLeft);
                }
    
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if (spriteFrame.x == 192)
                    {
                        spriteFrame.x = 224;
                    }
                    else
                    {
                        spriteFrame.x = 192;
                    }
                    if (playerPosition.x <= 160)
                    {
                        xImageLeft += 5;
                    }
                    else
                    {
                        playerPosition.x -= 5;
                    }
                    printf("%d %d\n", playerPosition.x, playerPosition.x - xImageLeft);
                }
    
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    if (spriteFrame.x == 128)
                    {
                        spriteFrame.x = 160;
                    }
                    else
                    {
                        spriteFrame.x = 128;
                    }
                    if (playerPosition.y >= 360)
                    {
                        yImageTop -= 5;
                    }
                    else
                    {
                        playerPosition.y += 5;
                    }
                    printf("%d %d\n", playerPosition.y, playerPosition.y - yImageTop);
                }
    
                if (event.key.keysym.sym == SDLK_UP)
                {
                    if (spriteFrame.x == 0)
                    {
                        spriteFrame.x = 32;
                    }
                    else
                    {
                        spriteFrame.x = 0;
                    }
                    if (playerPosition.y <= 120)
                    {
                        yImageTop += 5;
                    }
                    else
                    {
                        playerPosition.y -= 5;
                    }
                    printf("%d %d\n", playerPosition.y, playerPosition.y - yImageTop);
                }
            }
            if (event.type == SDL_QUIT)
            {
                quitGameLoop = 1;
            }
        }
        render_background(xImageLeft, yImageTop, gameImage, screen);
        // apply_surface(xImageLeft, yImageTop, gameImage, screen);
        SDL_BlitSurface(sprite, &spriteFrame, screen, &playerPosition);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    
    */
    Mix_FreeMusic(music);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
