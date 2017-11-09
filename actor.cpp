#include <SDL2/SDL_ttf.h>
#include <string>
#include "globals.h"
#include "actor.h"

Actor::Actor(SDL_Renderer* lRenderer)
{
    //Initialize the collision box
    mBox.x = 32;
    mBox.y = 32;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Initialize Jumping
    jumpLock = 0;
	loadMedia("assets/dot.bmp",lRenderer);
}

Actor::~Actor()
{
	texture.free();
}

bool Actor::loadMedia( std::string path , SDL_Renderer* lRenderer)
{
	bool success;
	//Load Actor texture
	if( !texture.loadFromFile( path , lRenderer ) )
	{
		printf( "Failed to load Actor texture!\n" );
		success = false;
	}
	return success;
}

void Actor::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
	    case SDLK_SPACE: if(!jumpLock) { jump(); }; break;

		//debug stuff
            case SDLK_o: jumpLock=0; jump(); break;
	    case SDLK_l: jumpLock=!jumpLock; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
	    case SDLK_SPACE: if(!jumpLock){mVelY = 0;} jumpLock = 1 ; break;
        }
    }
}

void Actor::jump()
{
    //Jump
    mVelY -= jumpVel;
    //jumpLock = 1;
}

bool Actor::canJump()
{
	return !jumpLock;
}

void Actor::gravity( Tile *tiles[] )
{
	int grav = 0;
    //is he in the air?
    if( ( mBox.y + DOT_HEIGHT < LEVEL_HEIGHT ) && ( !touchesFloor( mBox, tiles) ) )
    {
        if ( grav < DOT_VEL + 8 ) //check to see if he is terminal velocity yet
        {
            ++grav; //fall faster or ascend slower
        }
        else
        {
            //terminal velocity
            grav = DOT_VEL + 8;
        }
	mVelY = grav; 
   }
	else if( !touchesFloor(mBox, tiles) )
	{
		mBox.y -= grav;
		mVelY = 0;
		grav = 0;
	}
    else if( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT)
    {
	mVelY = 0;
        grav = 0;
        mBox.y = LEVEL_HEIGHT - DOT_HEIGHT;
    }
    else {
        grav = 0;
    }
}

void Actor::move( Tile *tiles[] )
{
    //Move the dot left or right
    mBox.x += mVelX;

    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //factor in gravity
    gravity(tiles);

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT )/* || touchesWall( mBox,tiles )*/ || touchesFloor( mBox, tiles ) )
    {
        //move back
        mBox.y -= mVelY;
	jumpLock = 0;
    }

}

void Actor::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Actor::render( SDL_Rect& camera )
{
    //Show the dot
	texture.render( mBox.x - camera.x, mBox.y - camera.y );
}
