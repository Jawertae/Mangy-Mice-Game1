//lol bitches

//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
//#include <fstream>
//#include <math.h>
#include "globals.h"
#include "actor.h"
#include "debug.h"

//extern int TOTAL_TILES;
//extern int SCREEN_WIDTH;
//extern int SCREEN_HEIGHT;


int main( int argc, char* args[] )
{
printf("wtf \n");
//std::string s = std::to_string(TOTAL_TILES);
//int tots = TOTAL_TILES;
//if(printf("what is reported total tiles: %s\n",tots) < 0){return 0;}


int totes = getTotalTiles();

printf("past second tilesthing");

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
printf("initialized \n");
		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];
//printf("total tiles: %s", s );
		//Load media
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
printf("media loaded \n" );
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			Debug debug;
			

			//fps stuff
			//LTimer fpsTimer;
			//LTimer capTimer;

			//int countedFrames = 0;
			//fpsTimer.start();

printf("should be at gameloop \n");

			//While application is running
			while( !quit )
			{
				//capTimer.start();
				//printf("lol");
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

				//more fps stuff
				//float avgFPS = countedFrames / (fpsTimer.getTicks() /1000.f );
				//if avgFPS > 2000000 ) { avgFPS = 0; }

				//Move the dot
				dot.move( tileSet );
				dot.setCamera( camera );
				debug.update(dot.canJump());

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}

				//Render dot
				dot.render( camera );
				debug.render();


				//Update screen
				SDL_RenderPresent( gRenderer );
				//++countedFrames;

				//int frameTicks = capTimer.getTicks();
				//if( frameTicks < SCREEN_TICKS_PER_FRAME )
				//{
				//	SDL_Delay( SCREEN_TICKS_PER+FRAME - frameTicks );
				//}

			}
		}

		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}


bool init()
{
	//Initialization flag
	bool success = true;
//printf( "screen height: %s" , SCREEN_HEIGHT );
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
printf("sdl init \n");
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
printf("window made? \n");
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_SOFTWARE || SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
printf("renderer created \n");
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//				get_Scalar();

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//Initialize Font
                                if( TTF_Init() == -1 )
                                {
                                    printf( "SDL_TTF could not Initialize! %s\n", TTF_GetError() );
                                    success = false;
                                }
			}
		}
	}

	return success;
}
