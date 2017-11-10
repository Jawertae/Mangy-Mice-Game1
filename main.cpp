#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
//#include <stdio.h>
#include <string>
#include "globals.h"
#include "actor.h"
#include "debug.h"
#include "timers.h"

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
LTexture gTileTexture;
TTF_Font* gFont = NULL;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];



int main( int argc, char* args[] )
{
	#ifdef DEBUG
	createLog();
	#endif

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		#ifdef DEBUG
		logText("Initialized");

		//getModes();
		#endif

		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		#ifdef DEBUG
		logText("Tileset Created: ",TOTAL_TILES);
		#endif

		//Load media
		if( !loadMedia( tileSet , gRenderer) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			#ifdef DEBUG
			logText("Media loaded" );
			#endif

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Actor dot = Actor(gRenderer);

			LTimer stepTimer;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			#ifdef DEBUG
			Debug debug = Debug(gRenderer);
			#endif

			#ifdef DEBUG
			logText("Gameloop Starting\n\n");
			#endif

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q )
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent( e );
				}

				float timeStep = stepTimer.getTicks()/1000.f;

				#ifdef DEBUG
				logText("Time per Step:",stepTimer.getTicks()/1000.f);
				#endif

				//Move the dot
				dot.move( timeStep, tileSet );
				dot.setCamera( camera );

				stepTimer.start();

				#ifdef DEBUG
				debug.update(dot.canJump());
				#endif

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}

				//Render dot
				dot.render( camera );

				#ifdef DEBUG
				debug.render();
				#endif

				//Update screen
				SDL_RenderPresent( gRenderer );

			}
		}

		//Free resources and close SDL
		close( tileSet );
	}
	#ifdef DEBUG
	closeLog();
	#endif

	return 0;
}


bool init()
{
	#ifdef DEBUG
	logText("Initialization Started");
	#endif

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		#ifdef DEBUG
		logText("SDL Initialized");
		#endif

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			#ifdef DEBUG
			logText("Window created.");
			#endif

			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);// || SDL_RENDERER_PRESENTVSYNC);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				#ifdef DEBUG
				logText("Renderer created.");
				#endif

				SDL_RenderSetLogicalSize(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);

				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 0, 255 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				#ifdef DEBUG
				logText("SDL_image Initialized.");
				#endif

				//Initialize Font
                                if( TTF_Init() == -1 )
                                {
                                    printf( "SDL_TTF could not Initialize! %s\n", TTF_GetError() );
                                    success = false;
                                }

				#ifdef DEBUG
				logText("SDL_TTF Initialized.");
				#endif

			}
		}
	}
	#ifdef DEBUG
	logText("Initialization function complete.");
	#endif
	return success;
}
