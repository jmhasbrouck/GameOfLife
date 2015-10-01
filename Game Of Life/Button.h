#pragma once
#include "SDL.h"
#include <vector>
class Button
{
public:
	Button();
	Button(int width, int height);
	~Button();
	void SetPosition(int x, int y);
	void HandleEvent(SDL_Event* e);
	void render();
	bool getState();
	SDL_Rect getRect();
	int getHeight();
	int getWidth();
	int getX();
	int getY();
	void SetDimensions(int width, int height);
	void ChangeState();
	void setStateTrue();
	void setStateFalse();
private:
	int BUTTON_WIDTH;
	int BUTTON_HEIGHT;
	int xPos;
	int yPos;
	SDL_Event* EVENT = NULL;
	SDL_Point mPosition;
	bool pushedButton;
	SDL_Rect fillRect;
};

