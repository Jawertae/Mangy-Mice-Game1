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
		SDL_Color textColor = {30,30,120};
		std::string varText;
		SDL_Renderer* lRenderer;
};



void createLog();

void logText(char*);

void logText(char*,char*);

void logText(char*,int);

void logText(char*,float);

void closeLog();

void getModes();

int get_Scalar();

#endif
