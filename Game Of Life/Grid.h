#pragma once
#include "Button.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
class Grid
{
public:
	Grid();
	~Grid();
	void drawGrid();
	int GreatestSquare(int &height, int &width);
	void PopulateGrid();
	bool init();
	void close();
	bool loadMedia();
	SDL_Texture* loadTexture(string path);
	void handlePushes(SDL_Event e);
	vector<vector<Button>> getGrid();
	void CheckSurroundingArea(Button &Current, int x, int y);
	Button getPlayButton();
	vector<vector<Button>> GRID;
	void CoutGrid();
	SDL_Renderer* getRenderer();
	Button getLinesButton();
	Button xDrawButton;
	void DrawX();
	void setDensity(int density1);
	void clearGrid();
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	void drawButtons();
	void Random();
private:
	int density;
	int gridHeight;
	int gridWidth;
	int SCREEN_WIDTH;
	int greatestSquare;
	int SCREEN_HEIGHT;
	int differenceW;
	int differenceH;
	bool initialized;
	int drawCount;
	int ColorCount;
	Button LinesButton;
	Button PlayButton;
	Button ClearButton;
	Button RandButton;
	SDL_Rect play;
	SDL_Rect* tempRect;
	SDL_Surface* text;
	TTF_Font* gFont;
	SDL_Color color;
	SDL_Texture* cTexture;
	int tWidth, tHeight;
	Button ColorButton;
	int ColorCount2, ColorCount3;
	//Loads individual image as texture
	

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The window renderer
	SDL_Renderer* gRenderer;
};

