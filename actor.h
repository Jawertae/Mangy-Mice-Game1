#ifndef ACTOR_H
#define ACTOR_H

//The dot that will move around on the screen

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


class Actor
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 16;
		static const int DOT_HEIGHT = 16;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 160;

		//Initializes the variables
		Actor( SDL_Renderer* lRenderer );
		~Actor();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and check collision against tiles
		void jump();
		void collideTile( Tile* );
		void gravity(float, Tile *tiles[] );
		void move(float timeStep, Tile *tiles[] );
		bool canJump();


		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect& camera );

    private:

		LTexture texture;
		bool jumpLock;
		static const int jumpVel = 320;

		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		float mPosX, mPosY;
		float mVelX, mVelY;
		int grav = 0;
		bool loadMedia( std::string path, SDL_Renderer* lRenderer );
};
#endif
