#include "Grid.h"
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Some code has been stolen from Lazy Foo without permission but this will not be distrubuted
//very messy and hard to read sorry

#include "SDL.h"
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Button.h"
#include "SDL_ttf.h"
#include <iostream>

using namespace std;
//Screen dimension constants
Grid::Grid()
{
	density = 5;
	SCREEN_WIDTH = 800;
	SCREEN_HEIGHT = 600;

	gridHeight = SCREEN_HEIGHT;
	gridWidth = SCREEN_WIDTH;
	GreatestSquare(gridHeight, gridWidth);
	if (gridWidth < SCREEN_WIDTH)
	{
		differenceW = SCREEN_WIDTH - gridWidth;
	}
	else if (gridHeight < SCREEN_HEIGHT)
	{
		differenceH = SCREEN_HEIGHT - gridHeight;
	}
	differenceW = differenceW / 2;
	differenceH = differenceH / 2;

	init();

	PopulateGrid();
	drawGrid();

	//SDL_Delay(2000);

}
void Grid::setDensity(int density1)
{
	density = density1;
	GRID.clear();
	PopulateGrid();
	drawGrid();
}

Grid::~Grid()
{
}


bool Grid::init()
{
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				initialized = true;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
					initialized = false;
				}
				if (TTF_Init() == -1)
				{
					success = false;
				}
			}
		}
	}

	return success;
}

bool Grid::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void Grid::close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Grid::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
void Grid::Random()
{
	if (gridWidth == gridHeight)
	{
		int numSquares = gridWidth / density;
		for (int i = 0; i < numSquares; i++)
		{
			for (int w = 0; w < numSquares; w++)
			{
				if (rand() % 5 == 0)
				{
					GRID[i][w].setStateTrue();
				}
			}
		}
	}

}
void Grid::drawGrid()
{
	if (initialized)
	{//Clear screen
		//Render red filled quad
		//	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		//		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		//SDL_RenderFillRect(gRenderer, &fillRect);
		//Render green outlined quad
		//SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		//SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		//SDL_RenderDrawRect(gRenderer, &outlineRect);
		//SDL_RenderDrawRect(gRenderer, &outlineRect);

		//Draw blue horizontal line
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		drawButtons(); //draws all buttons
		//draw squares
		for (int w = 0; w < GRID.size(); w++)
			{
				for (int i = 0; i < GRID[w].size(); i++)
				{
					if (GRID[w][i].getState())
					{
						if (ColorButton.getState())
						{
							ColorCount = rand()%255;
							ColorCount2 = rand() % 255;
							ColorCount3 = rand() % 255;
							SDL_SetRenderDrawColor(gRenderer, ColorCount3, ColorCount2,ColorCount, 0);
							
							
							SDL_RenderFillRect(gRenderer, &GRID[w][i].getRect());
						}//	drawGrid();
						else
						{
							SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);


							SDL_RenderFillRect(gRenderer, &GRID[w][i].getRect());
						}
					}
					else
					{
						SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
						SDL_RenderFillRect(gRenderer, &GRID[w][i].getRect());
						//drawGrid();

					}

				}
			}
		//draw lines if the lines button is not pressed, elsse do not draw lines
			if (!LinesButton.getState())
			{
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 255, 255);
				for (int i = differenceW; i < SCREEN_WIDTH - differenceW + 1; i = i + density)
				{
					SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
				}
				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0, 255);
				for (int i = differenceH; i < SCREEN_HEIGHT - differenceH; i = i + density)
				{
					SDL_RenderDrawLine(gRenderer, differenceW, 0 + i, SCREEN_WIDTH - differenceW, 0 + i);
				}
				//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 255);
			}
			/*SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
			//SDL_RenderClear(gRenderer);
			gFont = TTF_OpenFont("lazy.ttf", 28);
			color.a = 0;
			color.b = 255;
			color.g = 255;
			color.r = 255;
			loadFromRenderedText("Play", color);
			tempRect = &PlayButton.getRect();
			SDL_BlitSurface(cTexture, NULL, text, tempRect);
			*/

			SDL_RenderPresent(gRenderer);

			drawCount++;
			//}
		}
	
}
void Grid::DrawX()
{
	if (gridWidth == gridHeight)
	{
		int numSquares = gridWidth / density;
		for (int w = 0; w < numSquares; w++)
		{	
			GRID[w][w].setStateTrue();
			
		}
		for (int w = numSquares - 1; w >=0; w--)
		{
			GRID[w][numSquares-w - 1].setStateTrue();
		}
	}
	
}
int Grid::GreatestSquare(int &height, int &width)
{
	if (height > width)
	{
		height = width;
		return width;
	}
	else
	{
		width = height;
		return height;
	}
}
SDL_Renderer* Grid::getRenderer()
{
	return gRenderer;
}
void Grid::PopulateGrid()
{
	int height = SCREEN_HEIGHT;
	int width = SCREEN_WIDTH;
	GreatestSquare(height, width);
	Button TempButton = Button(density, density);
	vector<Button> TempVec;
	for (int w = SCREEN_HEIGHT - differenceH; w > 0; w = w - density)
	{
		GRID.push_back(TempVec);
	}
	for (int w = GRID.size() - 1; w >= 0; w--)
	{
		for (int i = SCREEN_WIDTH - differenceW - density; i >= differenceW; i = i - density)
		{
			TempButton.SetPosition(i, w*density);
			GRID[w].push_back(TempButton);
		}
	}

	PlayButton = Button(differenceW, SCREEN_HEIGHT / 8);
	PlayButton.SetPosition(0, 0);
	PlayButton.render();
	LinesButton = Button(differenceW, SCREEN_HEIGHT / 8);
	LinesButton.SetPosition(0, SCREEN_HEIGHT / 8);
	LinesButton.render();
	//LinesButton.ChangeState();
	xDrawButton = Button(differenceW, SCREEN_HEIGHT / 8);
	xDrawButton.SetPosition(0, (SCREEN_HEIGHT / 8) * 2 );
	xDrawButton.render();
	ClearButton = Button(differenceW, SCREEN_HEIGHT / 8);
	ClearButton.SetPosition(0, (SCREEN_HEIGHT / 8) * 3);
	ClearButton.render();
	ColorButton = Button(differenceW, SCREEN_HEIGHT / 8);
	ColorButton.SetPosition(0, (SCREEN_HEIGHT / 8) * 4);
	RandButton = Button(differenceW, SCREEN_HEIGHT / 8);
	RandButton.SetPosition(0, (SCREEN_HEIGHT / 8) * 5);
}
void Grid::handlePushes(SDL_Event e)
{
	PlayButton.HandleEvent(&e);
	LinesButton.HandleEvent(&e);
	xDrawButton.HandleEvent(&e);
	ClearButton.HandleEvent(&e);
	ColorButton.HandleEvent(&e);
	RandButton.HandleEvent(&e);
	for (int w = 0; w < GRID.size(); w++)
	{
		for (int i = 0; i < GRID[w].size(); i++)
		{
			GRID[w][i].HandleEvent(&e);
		}
	}
	//SDL_RenderClear(gRenderer);
}
vector<vector<Button>> Grid::getGrid()
{
	return GRID;
}
Button Grid::getPlayButton()
{
	return PlayButton;
}
void Grid::CoutGrid()
{
	cout << endl;
	for (int j = 0; j < GRID.size(); j++)
	{
		for (int i = 0; i < GRID[j].size(); i++)
		{
			cout << GRID[j][i].getState() << " ";
		}
		cout << endl;
	}
	cout << endl;
}
Button Grid::getLinesButton()
{
	return LinesButton;
}
void Grid::clearGrid()
{
	for (int w = 0; w < GRID.size(); w++)
	{
		for (int i = 0; i < GRID[w].size(); i++)
		{
			GRID[w][i].setStateFalse();
		}
	}
}
bool Grid::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Shaded(gFont, textureText.c_str(), textColor , textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		cTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (cTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			tWidth = textSurface->w;
			tHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return cTexture != NULL;
}
void Grid::drawButtons()
{
	if (!PlayButton.getState())
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
		SDL_RenderFillRect(gRenderer, &PlayButton.getRect());
		//drawGrid();
		//SDL_RenderPresent(gRenderer);

	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, &PlayButton.getRect());
		//drawGrid();
		//SDL_RenderPresent(gRenderer);

	}

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(gRenderer, &ClearButton.getRect());
	if (ClearButton.getState())
	{
		clearGrid();
		ClearButton.setStateFalse();
	}


	if (!LinesButton.getState())
	{
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 0);
		SDL_RenderFillRect(gRenderer, &LinesButton.getRect());
		//drawGrid();
		//SDL_RenderPresent(gRenderer);

	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, &LinesButton.getRect());
		//drawGrid();
		//SDL_RenderPresent(gRenderer);

	}
	if (!xDrawButton.getState())
	{
		SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
		SDL_RenderFillRect(gRenderer, &xDrawButton.getRect());
		//drawGrid();
		//SDL_RenderPresent(gRenderer);

	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, &xDrawButton.getRect());
		//Create X pattern
		DrawX();
		//drawGrid();
		//SDL_RenderPresent(gRenderer);
	}
	if (!ColorButton.getState())
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 0);
		SDL_RenderFillRect(gRenderer, &ColorButton.getRect());
	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, &ColorButton.getRect());
	}
	if (!RandButton.getState())
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 0);
		SDL_RenderFillRect(gRenderer, &RandButton.getRect());
	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, &RandButton.getRect());
		Random();
	
	}
}