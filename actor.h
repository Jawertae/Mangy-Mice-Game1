#ifndef ACTOR_H
#define ACTOR_H

//The dot that will move around on the screen

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 20;

		//Initializes the variables
		Dot();
		~Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and check collision against tiles
		void jump();
		void gravity();
		void move( Tile *tiles[] );
		bool canJump();


		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect& camera );

    private:

		LTexture texture;
		bool jumpLock;
		static const int jumpVel = 10;

		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY;
		bool loadMedia(std::string path);
};
#endif
