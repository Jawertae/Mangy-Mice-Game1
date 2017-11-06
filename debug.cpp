#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "globals.h"
#include "debug.h"



Debug::Debug(SDL_Renderer* rendPtr)
{
	textColor = {3,3,3};
	jumpBool = "unset";
	lRenderer = rendPtr;
}
Debug::Debug(SDL_Renderer* rendPtr, int r, int g, int b )
{
	textColor = {r,g,b};
	jumpBool = "unset";
	lRenderer = rendPtr;
}

void Debug::update()
{

}

void Debug::update(bool canJump)
{

	if(canJump){jumpBool="jump";}
	else {jumpBool="no";}

	if( !debugText.loadFromRenderedText( jumpBool , textColor, lRenderer) )
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
