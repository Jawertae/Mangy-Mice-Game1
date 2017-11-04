//lol bitches

//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <math.h>
#include "globals.h"
#include "textures.h"
#include "tiles.h"
#include "actor.h"
#include "debug.h"



int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
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



			//While application is running
			while( !quit )
			{
				//capTimer.start();

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
