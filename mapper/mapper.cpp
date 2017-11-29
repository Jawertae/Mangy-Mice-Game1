#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

using namespace std;

int getArgs(int,const char**);

int checkFileName(char*);

void genText(char*,char*,int,int);

int CHOICE = 0;
int FILL = 1;
string FILLTEXT = "10";
char* FILENAME = "DEFAULT";
int OUTPUT = 0;
string W_TEXT = "5";
string H_TEXT = "5";
int WIDTH = 5;
int HEIGHT = 5;

static const char* OPTSTRING = "rs0opci:l:w:h:?";

int main(int argc, const char *argv[])
{

	if(argc>1)
	{
		if(getArgs(argc,argv) == -800)
		{
			return 0;
		}
	}

	if(argc<=1)
	{
		cout << "This program requires at least one argument\nuse -? to learn more\n";
		return -1;
	}

	if(FILENAME == "DEFAULT")
	{
		cout << "No input filename was given so the default \"test.bin\" will be used.\n";
		FILENAME = "test.bin";
	}
	if(CHOICE == 0 && OUTPUT == 0)
	{
		cout << "No instruction given for " << FILENAME << " please use a generator and/or output option as well.\n";
		return -2;
	}

	stringstream tWidth(W_TEXT);
	stringstream tHeight(H_TEXT);

	tWidth >> WIDTH;
	tHeight >> HEIGHT;

	//input/generator types
	if(CHOICE==1) // fills a mapfile with random data		(-r)
	{
		randMap(FILENAME,WIDTH,HEIGHT);
		genText(FILENAME,"randomly ",WIDTH,HEIGHT);
	}
	if(CHOICE==2) // fills a mapfile with zeros			(-0)
	{
		//to be implemented later
		genText(FILENAME,"with 0s ",WIDTH,HEIGHT);
	}
	if(CHOICE==3) // fills a mapfile with user selected data	(-s)
	{
		writeMap(FILENAME,WIDTH,HEIGHT);
		genText(FILENAME,"using user input ",WIDTH,HEIGHT);
	}


	//output types
	if(OUTPUT==1) // outputs data about a mapfile			(-o)
	{
		readMap(FILENAME);
	}
	if(OUTPUT==2) // makes a physics mapfile			(-p)
	{
		if (physicsMap(FILENAME) >=0)
		{
			cout << ".phys file generated from " << FILENAME << ".\n";
		}
	}
	if(OUTPUT==3) // convert tilemap.txt to .map			(-c)
	{
		if (tileMapConv(FILENAME) >=0)
		{
			cout << ".map file generated from " << FILENAME << ".\n";
		}
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
			case 'c':
				OUTPUT = 3;
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
				break;
			case '?':
				if (optopt == 'f'||optopt == 'i'||optopt == 'w'||optopt == 'h')
				{
					cout << "option " << optopt << " requires an argument.\n";
				}
				cout << "Required Arguments:\n-i (filename) for input filename\n\tFiles can be .txt, .map, or .bin\n\n";
				cout << "Generation Arguments:\n-w (num) to change width (default 10)\n-h (num) to change height (default 10)\n";
				cout << "-s to fill map with user selected data\n-r to fill map with random data\n\n";
				cout << "Conversion Arguments:\n-c convert from a raw tILE file (.txt) to temporary .map file\n\n";
				cout << "Output Arguments:\n-o to output formatted map info to stdout\n-p to output a physics mapfile for selected map\n";
				cout << "\n-? to view this help\n";
				return -800;
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
	if( string(option).find(".txt") != string::npos || string(option).find(".map") != string::npos || string(option).find(".bin") != string::npos )
	{
		FILENAME = option;
	}
	else
	{
		cout << "filenames must be .bin, .map, or .txt\n";
		return 0;
	}
	return 1;
}

void genText(char* file,char* gentext,int w,int h)
{
	cout << file << " generated " << gentext << "with width=" << w << " and height=" << h << ".\n";

}
