//class for all debug actions
class Debug
{
	public:
		Debug();
		Debug(int,int,int);
		void update();
		void render();
		void render(int,int);
		
	private:
		LTexture debugText;
		SDL_Color textColor;
		char * jumpBool;
};
