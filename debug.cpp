Debug::Debug()
{
	textColor = {3,3,3};
	jumpBool = "unset";
}
Debug::Debug(int r, int g, int b)
{
	textColor = {r,g,b};
	jumpBool = "unset";
}

void Debug::update(Bool canJump)
{
	
	if(canJump){jumpBool="jump";}
	else {jumpBool="no";}

	if( !debugText.loadFromRenderedText( jumpBool , textColor) )
	{
		printf("failed to load debug text");
	}

}

void Debug::render()
{
	debugText.render(40,40);
}

void Debug::render(int x,int y)
{
	debugText.render(x,y);
}
