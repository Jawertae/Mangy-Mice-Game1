//class for all debug actions
class Debug
{
	public:
		Debug();
		Debug(int,int,int);
		void update();
		void update(bool);
		void render();
		void render(int,int);

	private:
		LTexture debugText;
		SDL_Color textColor = {3,3,3};
		std::string jumpBool;
};
