#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <fstream>
#include "globals.h"
#include "debug.h"

static std::ofstream logfile;

Debug::Debug(SDL_Renderer* rendPtr)
{
	textColor = {30,30,130};
	varText = "unset";
	lRenderer = rendPtr;
}
Debug::Debug(SDL_Renderer* rendPtr, int r, int g, int b )
{
	textColor = {r,g,b};
	varText = "unset";
	lRenderer = rendPtr;
}

void Debug::update()
{

}

void Debug::update(bool dispBool)
{

	if(dispBool){varText="jump";}
	else {varText="no";}

	if( !debugText.loadFromRenderedText( varText , textColor, lRenderer) )
	{
		printf("failed to load debug text");
	}

}

void Debug::render()
{
	debugText.render(40,40);
}

void Debug::render(int x,int y)
{
	debugText.render(x,y);
}

void createLog()
{
	char runTimeStr[21];
	time_t t = time(0);
	strftime(runTimeStr,21,"%Y-%m-%d %H:%M:%S ",localtime(&t));

	logfile.open("log.txt",std::ios::out | std::ios::app);
	logfile << "Runtime Log: " << runTimeStr <<"\n\n";
}

void logText(char* text)
{
	logfile << text << "\n";
}

void logText(char* text,char* error)
{
	logfile << text << error << "\n";	
}

void logText(char* text,int out)
{
	logfile << text << out << "\n";	
}

void logText(char* text,float out)
{
	logfile << text << out << "\n";	
}

void closeLog()
{

	logfile << "\nExecution Complete\n\n";
	logfile.close();
}

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

			logText("\nModes Get!");
		}
	}

}
/*
int get_Scalar()
{
	SDL_DisplayMode* info = NULL;
	float hor_scale = 1.0;
	float vert_scale = 1.0;
	int scalar = 1;
	//int hor = 0;
	//int vert = 0;

	if( SDL_GetDesktopDisplayMode(0, info) != 0 )
	{
		printf("Get Current Display Failed: %s\n", SDL_GetError() );
		return 1;
	}
	else
	{

		printf("Supposedly got current display\n");

		if( info->w > 0 ) { SCREEN_WIDTH_TRUE = info->w; }
		else{ return 1; }
		if( info->h > 0 ) { SCREEN_HEIGHT_TRUE = info->h; }
		else{ return 1; }

		if(1)
		{
			hor_scale = (float)SCREEN_WIDTH_TRUE/(float)SCREEN_WIDTH;
			vert_scale = (float)SCREEN_HEIGHT_TRUE/(float)SCREEN_HEIGHT;

			scalar = (int)(!(vert_scale<hor_scale)?hor_scale:vert_scale);
		}
	}

	//debug
	printf( "Screen Dimensions: %s",SCREEN_WIDTH_TRUE, SCREEN_HEIGHT_TRUE );
	printf( "Horizontal: %d\nVertical: %d\nFinal: %d\n",hor_scale,vert_scale, scalar );

	return scalar;
}

*/

