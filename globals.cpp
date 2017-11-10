#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <string>
//#include <iostream.h>
#include "globals.h"
#include "mapper/parser.h"
#include "debug.h"

int SCREEN_WIDTH_TRUE = 480;
int SCREEN_HEIGHT_TRUE = 272;


LevelInfo::LevelInfo()
{
	h = LEVEL_HEIGHT;
	w = LEVEL_WIDTH;
}

ScreenInfo::ScreenInfo()
{
	h = SCREEN_HEIGHT;
	w = SCREEN_HEIGHT;
}

int getTotalTiles()
{
	printf("totalfiles");
	return TOTAL_TILES;
}

bool loadMedia( Tile* tiles[] , SDL_Renderer* lRenderer)
{
	//Loading success flag
	bool success = true;

	//Load tile texture
	if( !gTileTexture.loadFromFile( "assets/test_tiles.png",lRenderer ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	#ifdef DEBUG
	logText("Loaded Tile Texture.");
	#endif

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	#ifdef DEBUG
	logText("Rendered all Tiles.");
	#endif

        //Load TTF
        gFont = TTF_OpenFont( "assets/ph.ttf", 28 );
        if( gFont == NULL)
        {
            printf( "Failed to load font!\n" );
            success = false;
        }

	#ifdef DEBUG
	logText("Loaded Font.");
	#endif

	return success;
}



Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

	tileTotal = TOTAL_TILES;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

int Tile::getTotal()
{
	return tileTotal;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}


void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] == NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

        //Free Global Font
        TTF_CloseFont( gFont );
        gFont = NULL;

	//Free loaded images
	gTileTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "assets/test2.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		#ifdef DEBUG
		logText("Loaded Map File.");
		#endif

		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{

			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if( tilesLoaded )
		{
			const int w = 4;
			const int h = 4;
			int j = 0;
			int k = 0;
			for(int i = 0;i< w*h; i++)
			{
				gTileClips[i].x = j * 32;
				gTileClips[i].y = k * 32;
				gTileClips[i].w = TILE_WIDTH;
				gTileClips[i].h = TILE_HEIGHT;
				j++;
				if (j >= w){k++;j=0;}
			}
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() != 11 ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

bool checkFall( SDL_Rect a, SDL_Rect b )
{

	//a is moving, b is stationary. all calculations are based on middle x of a and entire x plane of b

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

	//int midATop,midABot;

    //Calculate the sides of rect A
    //leftA = a.x;
    //rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
	int midA =  a.x + (a.h/2);

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    //bottomB = b.y + b.h;

    //if middle of a falls between left and right of b and and all of a is higher than b
    if( bottomA < topB && topA < topB && leftB < midA && midA < rightB )
    {
		return false;
    }
    return true;
}

bool touchesFloor( SDL_Rect box, Tile* tiles[] )
{	
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
	//If the tile is a wall type tile
	if( ( tiles[ i ]->getType() == 1 ) )
	{
	    //If the collision box touches the wall tile
	    if( checkFall( box, tiles[ i ]->getBox() ) && checkCollision( box, tiles[ i ]->getBox() ) )
	    {
		return true;
	    }
	}
    }

    //If no wall tiles were touched
    return false;
}


Tile* getCollide( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() != 11 ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return tiles[i];
            }
        }
    }
//return NULL;
}

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path , SDL_Renderer* lRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( lRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor , SDL_Renderer* lRenderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
                mTexture = SDL_CreateTextureFromSurface( lRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
