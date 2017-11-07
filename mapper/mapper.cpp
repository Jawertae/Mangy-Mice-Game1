
//#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include "mapper.h"
#include "parser.h"

using namespace std;

int getArgs(int,const char**);

int CHOICE = 3;
int FILL = 1;
string FILLTEXT = "10";
static const char* OPTSTRING = "ros0f:?";

int main(int argc, const char *argv[])
{

	if(argc>1)
	{
		getArgs(argc,argv);
	}

	stringstream tFill(FILLTEXT);

	tFill >> FILL;

	if(CHOICE==1)
	{
		randMap(FILL);
	}
	if(CHOICE==3)
	{
		writeMap(FILL);
	}
	if(CHOICE==4)
	{
		readMap();
	}
	if(CHOICE==2)
	{
		//to be implemented later
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
				CHOICE = 4;
				break;
			case 'f':
				FILLTEXT = optarg;
				break;
			case '?':
				if (optopt == 'f')
				{
					//fprint("option -%c requires an argument.\n",optopt)
				}
				break;
			default:
				break; //abort();
		}
		opt = getopt(argc,(char **)argv,OPTSTRING);
	}
return 1;
}
