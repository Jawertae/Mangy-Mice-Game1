#ifndef DEBUG_H
#define DEBUG_H

//class for all debug actions
class Debug
{
	public:
		Debug(SDL_Renderer*);
		Debug(SDL_Renderer*,int,int,int);
		void update();
		void update(bool);
		void render();
		void render(int,int);

	private:
		LTexture debugText;
		SDL_Color textColor = {3,3,3};
		std::string jumpBool;
		SDL_Renderer* lRenderer;
};
#endif
