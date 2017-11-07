#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

using namespace std;

int getArgs(int,const char**);

int checkFileName(char*);

int CHOICE = 3;
int FILL = 1;
string FILLTEXT = "10";
char* FILENAME = "test.bin";
bool OUTPUT = false;

static const char* OPTSTRING = "ros0i:f:?";

int main(int argc, const char *argv[])
{

	if(argc>1)
	{
		getArgs(argc,argv);
	}

	stringstream tFill(FILLTEXT);

	tFill >> FILL;

	if(CHOICE==1) // fills a mapfile with random data
	{
		randMap(FILENAME,FILL);
	}
	if(CHOICE==2) // fills a mapfile with zeros
	{
		//to be implemented later
	}
	if(CHOICE==3) // fills a mapfile with user selected data
	{
		writeMap(FILENAME,FILL);
	}
	if(OUTPUT) // outputs data about a mapfile
	{
		readMap(FILENAME);
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
				OUTPUT = true;
				break;
			case 'i':
				checkFileName(optarg);
				break;
			case 'f':
				FILLTEXT = optarg;
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
