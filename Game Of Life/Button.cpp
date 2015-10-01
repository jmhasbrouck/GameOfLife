#include "Button.h"
#include "SDL.h"

Button::Button(int width, int height)
{
	xPos = 0;
	yPos = 0;
	pushedButton = false;
	BUTTON_WIDTH = width;
	BUTTON_HEIGHT = height;
	fillRect = { 0, 0, 0, 0 };

}
Button::Button()
{
}
void Button::SetDimensions(int width, int height)
{

}
void Button::ChangeState()
{
	if (pushedButton)
	{
		pushedButton = false;
	}
	else
	{
		pushedButton = true;
	}
	render();
}
void Button::setStateFalse()
{
	pushedButton = false;
	render();
}
void Button::setStateTrue()
{
	pushedButton = true;
	render();
}
Button::~Button()
{
}
void Button::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
	render();
}
void Button::HandleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = false;
		if (xPos > x)
		{
			inside = false;
		}
		else if (xPos + BUTTON_WIDTH < x)
		{
			inside = false;
		}
		else if (yPos > y)
		{
			inside = false;
		}
		else if (yPos + BUTTON_HEIGHT < y)
		{
			inside = false;
		}
		else
		{
			inside = true;
		}
		if (inside && e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (pushedButton)
			{
				pushedButton = false;
			}
			else
			{
				pushedButton = true;
			}

		}
	}

}
void Button::render()
{

	fillRect = { xPos, yPos, BUTTON_WIDTH - 1, BUTTON_HEIGHT - 1 };

}
SDL_Rect Button::getRect()
{
	return fillRect;
}
bool Button::getState()
{
	return pushedButton;
}
int Button::getHeight()
{
	return BUTTON_HEIGHT;
}
int Button::getWidth()
{
	return BUTTON_WIDTH;
}
int Button::getX()
{
	return xPos;
}
int Button::getY()
{
	return yPos;
}
