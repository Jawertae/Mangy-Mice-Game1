#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int data = -1;

	int tile = -1;
	string fg;
	bool z = false;
	int physics = -1;
	int rot = -1;
	string flip;
	bool mirror = false;


	ofstream mapfile( "test.bin" , ios::binary | ios::in | ios::out);
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
	cout << "\nTile:        " << tile;
	cout << "\nForeground:  " << ((z)?"128":"0");
	cout << "\nPhysics:     " << physics*8;
	cout << "\nMirrored:    " << ((mirror)?"4":"0");
	cout << "\nRotation:    " << rot-1;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
	#endif

	//bit-wise arithmetic

	if(z==true){data = 128;}
	data += physics * 8;
	if(mirror==true){data += 4;}
	data += rot - 1;


	#ifdef Debug
	cout << "\nTile Bytes:" << tile;
	cout << "\nFlag Bytes:" << data << "\n";
	#endif

	//actual file write

	mapfile.write((char*) &tile, 1);
	mapfile.write((char*) &data, 1);


	return 0;
}
