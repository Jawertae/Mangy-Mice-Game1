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

void closeLog()
{

	logfile << "\nExecution Complete\n\n";
	logfile.close();
}


