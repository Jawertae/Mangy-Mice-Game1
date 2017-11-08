#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <bitset>

#include "parser.h"

using namespace std;

int readMap(char* filename)
{
	int tile;
	int data;

	int w;
	int h;

	string flags;

	bool z;
	int physics;
	bool mirror;
	int rotation;

	fstream binary(filename,ios::binary | ios::in);

	if(binary.is_open())
	{
		w = binary.get();
		h = binary.get();

		cout << "Width of Level: " << w;
		cout << "\nHeight of Level: " << h << "\n";

		while(!binary.eof())
		{

			for(int i = 0;i<w;i++)
			{
				tile = binary.get();
				data = binary.get();

				if(binary.eof()){break;}

				#ifdef DEBUG
				cout << "\nTile Dec: " << (int)tile;
				cout << "\nData Dec: " << (int)data << "\n";
				#endif

				//cout << toBinary(data) << "\n";
				flags = bitset<8>(data).to_string();

				z = (bitset<1> (flags.substr(0,1)).to_ulong()?true:false);
				physics = bitset<4> (flags.substr(1,4)).to_ulong();
				mirror = (bitset<1> (flags.substr(5,1)).to_ulong()?true:false);
				rotation = bitset<2> (flags.substr(6,2)).to_ulong();

				#ifdef DEBUG
				cout << flags << "\n";
				#endif
				cout << setfill('0');
				cout << "[" << setw(3) << tile << "." << z << "." << setw(2) << physics << "." << mirror << "." << rotation << "] ";
			}
			cout << "\n";
		}
		binary.close();
	}

	else
	{
		cout << "Couldn't open file for reading.";
		return 0;
	}
	cout << "\n";
	return 1;

}

int writeMap(char* filename, int width, int height)
{
	int data = 0;

	int tile = -1;
	string fg;
	bool z = false;
	int physics = -1;
	int rot = -1;
	string flip;
	bool mirror = false;


	ofstream mapfile( filename , ios::binary | ios::out | ios::trunc);
	while( tile > 256||tile < 1)
	{
		cout << "Tile Between 1 and 256: ";
		cin >> tile;
	}

	cout << "Foreground? (y or n): ";
	cin >> fg;

	while( physics > 15 || physics < 0)
	{
		cout << "Physics Type between 1 and 15 (0 for nonsolid): ";
		cin >> physics;
	}

	while ( rot > 4 || rot < 1)
	{
		cout << "Rotation between 1 and 4 (N,E,S,W): ";
		cin >> rot;
	}
	cout << "Mirrored? (y or n): ";
	cin >> flip;

	if(fg=="y" || fg=="Y" || fg=="1"){z=true;}
	if(flip=="y" || flip=="Y" || flip=="1"){mirror=true;}

	#ifdef DEBUG
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\nTile:        " << setw(5) << tile << setw(5) << tile;
	cout << "\nForeground:  " << setw(5) << ((z)?"128":"0") << setw(5) << z;
	cout << "\nPhysics:     " << setw(5) << physics*8 << setw(5) << physics;
	cout << "\nMirrored:    " << setw(5) << ((mirror)?"4":"0") << setw(5) << mirror;
	cout << "\nRotation:    " << setw(5) << rot-1 << setw(5) << rot;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
	#endif

	//bit-wise arithmetic

	if(z==true){data += 128;}
	data += physics * 8;
	if(mirror==true){data += 4;}
	data += rot - 1;


	#ifdef DEBUG
	cout << "\nTile Bytes:" << tile;
	cout << "\nFlag Bytes:" << data << "\n";
	#endif

	//actual file write

	mapfile.write((char*) &width,1);
	mapfile.write((char*) &height,1);

	for(int i = 0; i < (width * height); i++)
	{
	mapfile.write((char*) &tile, 1);
	mapfile.write((char*) &data, 1);
	}
	mapfile.close();

	return 0;
}

int randMap(char* filename, int width,int height)
{
	int tile;
	int data;

	srand(time(NULL));

	ofstream mapfile(filename,ios::binary | ios::out | ios::trunc);

	mapfile.write( (char*) &width,1);
	mapfile.write( (char*) &height,1);

	for(int i = 0 ; i < (width*height) ; i++)
	{
		tile = rand() % 256;
		data = rand() % 256;

		mapfile.write( (char*)&tile, 1 );
		mapfile.write( (char*)&data, 1 );
	}
	mapfile.close();
	return 0;
}

int physicsMap(char* filename)
{
	int tile;
	int data;

	int w;
	int h;

	string physFilename(filename);

	physFilename.replace(physFilename.find('.'),12,".phys");

	string flags;

	bool z;
	int physics;
	bool mirror;
	int rotation;

	ifstream binary(filename,ios::binary | ios::in);
	ofstream physicsFile(physFilename,ios::out | ios::trunc);

	if(!physicsFile.is_open())
	{
		cout << "Couldn't open file for reading.";
		return 0;
	}
	if(binary.is_open())
	{
		w = binary.get();
		h = binary.get();

		while(!binary.eof())
		{
			for(int i = 0;i<w;i++)
			{
				tile = binary.get();
				data = binary.get();

				if(binary.eof()){break;}

				flags = bitset<8>(data).to_string();

				//z = (bitset<1> (flags.substr(0,1)).to_ulong()?true:false);
				physics = bitset<4> (flags.substr(1,4)).to_ulong();
				//mirror = (bitset<1> (flags.substr(5,1)).to_ulong()?true:false);
				//rotation = bitset<2> (flags.substr(6,2)).to_ulong();

				physicsFile << setfill('0') << setw(2) << physics << " ";
			}
			physicsFile << "\n";
		}
		binary.close();
		physicsFile.close();
	}

return 1;
}





