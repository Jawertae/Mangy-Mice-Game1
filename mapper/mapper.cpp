#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

using namespace std;

int getArgs(int,const char**);

int checkFileName(char*);

int CHOICE = 0;
int FILL = 1;
string FILLTEXT = "10";
char* FILENAME = "test.bin";
int OUTPUT = 0;
string W_TEXT = "5";
string H_TEXT = "5";
int WIDTH = 5;
int HEIGHT = 5;

static const char* OPTSTRING = "rs0opi:l:w:h:?";

int main(int argc, const char *argv[])
{

	if(argc>1)
	{
		getArgs(argc,argv);
	}

	stringstream tWidth(W_TEXT);
	stringstream tHeight(H_TEXT);

	tWidth >> WIDTH;
	tHeight >> HEIGHT;

//input/generator types
	if(CHOICE==1) // fills a mapfile with random data
	{
		randMap(FILENAME,WIDTH,HEIGHT);
	}
	if(CHOICE==2) // fills a mapfile with zeros
	{
		//to be implemented later
	}
	if(CHOICE==3) // fills a mapfile with user selected data
	{
		writeMap(FILENAME,WIDTH,HEIGHT);
	}
//output types
	if(OUTPUT==1) // outputs data about a mapfile
	{
		readMap(FILENAME);
	}
	if(OUTPUT==2) // makes a physics mapfile
	{
		physicsMap(FILENAME);
	}
	return 0;
}

int getArgs(int argc, const char **argv)
{
	int opt = getopt(argc,(char **)argv,OPTSTRING);

	while (opt != -1)
	{
		switch (opt)
		{
			case 'r':
				CHOICE = 1;
				break;
			case '0':
				CHOICE = 2;
				break;
			case 's':
				CHOICE = 3;
				break;
			case 'o':
				OUTPUT = 1;
				break;
			case 'i':
				checkFileName(optarg);
				break;
			case 'l':
			case 'w':
				W_TEXT = optarg;
				break;
			case 'h':
				H_TEXT = optarg;
				break;
			case 'f':
				FILLTEXT = optarg;
				break;
			case 'p':
				OUTPUT = 2;
				//checkFileName(optarg);
				break;
			case '?':
				if (optopt == 'f'||optopt == 'i')
				{
					cout << "option " << optopt << " requires an argument.\n";
				}
				cout << "i for filename, f for fill, r or random, o or output\n";
				break;
			default:
				break; //abort();
		}
		opt = getopt(argc,(char **)argv,OPTSTRING);
	}
return 1;
}


int checkFileName(char* option)
{
	if( string(option).find(".bin") != string::npos)
	{
		FILENAME = option;
	}
	else
	{
		cout << "filenames must be .bin\n";
		return 0;
	}
	return 1;
}