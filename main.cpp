#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "globals.h"
#include "actor.h"
#include "debug.h"


SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
LTexture gTileTexture;
TTF_Font* gFont = NULL;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];


void getModes()
{
	int display = 0;
	int i;
	int displayCount;
	SDL_DisplayMode* mode;
	Uint32 f;

	int www;

	SDL_Log("GetNumVideoDisplays(): %i",SDL_GetNumVideoDisplays());

	displayCount = SDL_GetNumDisplayModes(display);
	if(displayCount < 1)
	{
		printf("Getting number of display modes failed %s\n",SDL_GetError());
	}
	else
	{
		for (i = 0; i < displayCount; ++i)
		{
			if(SDL_GetDisplayMode(display,i,mode) != 0)
			{
				printf("Couldnt get display mode number %d: %s\n",i,SDL_GetError());
			}
			f = mode->format;

			//www = mode->w;

			//SDL_Log("Mode %i\tbpp%i\t%s\t%i x %i",i,SDL_BITSPERPIXEL(f),SDL_GetPixelFormatName(f),mode->w,mode->h);

			printf("\nModes Get!\n");
		}
	}

}



int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		#ifdef DEBUG
		printf("Initialized\n");

		getModes();
		#endif

		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		#ifdef DEBUG
		printf("Tileset Created: %d\n",TOTAL_TILES);
		#endif

		//Load media
		if( !loadMedia( tileSet , gRenderer) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			#ifdef DEBUG
			printf("Media loaded\n" );
			#endif

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Actor dot = Actor(gRenderer);

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			#ifdef DEBUG
			Debug debug = Debug(gRenderer);
			#endif

			#ifdef DEBUG
			printf("Gameloop Starting\n\n");
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

				//Move the dot
				dot.move( tileSet );
				dot.setCamera( camera );

				#ifdef DEBUG
				debug.update(dot.canJump());
				#endif

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

	return 0;
}


bool init()
{
	#ifdef DEBUG
	printf("Initialization Started");
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
		printf("SDL Initialized \n");
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
			printf("Window created.\n");
			#endif

			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_SOFTWARE || SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				#ifdef DEBUG
				printf("Renderer created.\n");
				#endif

				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xAA, 0xAA, 0xAA, 0xAA );
//get scalar
//				get_Scalar();

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				#ifdef DEBUG
				printf("SDL_image Initialized\n");
				#endif

				//Initialize Font
                                if( TTF_Init() == -1 )
                                {
                                    printf( "SDL_TTF could not Initialize! %s\n", TTF_GetError() );
                                    success = false;
                                }

				#ifdef DEBUG
				printf("SDL_TTF Initialized\n");
				#endif

			}
		}
	}
	#ifdef DEBUG
	printf("Initialization function complete\n");
	#endif
	return success;
}
