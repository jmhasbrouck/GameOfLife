#include "Rules.h"
#include "Grid.h"
#include "Button.h"
#include "SDL.h"
#include <iostream>
using namespace std;
Rules::Rules()
{
	Grid grid = Grid();
	SDL_Event e;
	int count=0;

	grid.setDensity(3);

	for (int i = 0; i < grid.GRID.size(); i++)
	{
		tempGrid.push_back(temp);
	}
	for (int j = 0; j < grid.GRID.size(); j++)
	{
		for (int i = 0; i < grid.GRID[j].size(); i++)
		{
			tempGrid[j].push_back(false);
		}
	}

	bool quit = false;
	while (!quit)
	{
		SDL_WaitEvent(&e);
		if (e.type == SDL_QUIT)
		{
			quit = true;
			break;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			grid.handlePushes(e);
			while (grid.getPlayButton().getState())
			{
				Check(grid);
				grid.drawGrid();
				SDL_Delay(5);
				SDL_PollEvent(&e);
				
				
				grid.handlePushes(e);
				grid.getPlayButton().ChangeState();
				
				if (e.type == SDL_QUIT)
				{
					quit = true;
					break;
				}
				
			}
			

			grid.drawGrid();
		}

	}
}
void Rules::Check(Grid &grid)
{
	for (int j = 0; j < grid.GRID.size(); j++)
	{
		for (int i = 0; i < grid.GRID[j].size(); i++)
		{
			tempGrid[j][i] = grid.GRID[j][i].getState();
		}
	}

	
		
			liveordie(grid);
		

	
	for (int w = 0; w < grid.GRID.size(); w++)
	{
		for (int i = 0; i < grid.GRID[w].size(); i++)
		{
			if (tempGrid[w][i])
			{
				grid.GRID[w][i].setStateTrue();
			}
			else
			{
				grid.GRID[w][i].setStateFalse();
			}
		}
	}
}
void Rules::liveordie(Grid &grid)
{
	bool zeroI = false;
	bool zeroW = false;
	bool maxI = false;
	bool maxW = false;
	
	int neighbors = 0;

	for (int w = 0; w < grid.GRID.size(); w++)
	{
		for (int i = 0; i < grid.GRID[w].size(); i++)
		{
			zeroI = false;
			zeroW = false;
			maxI = false;
			maxW = false;
			neighbors = 0;
			if (i == 0)
			{
				zeroI = true;
			}
			if (w == 0)
			{
				zeroW = true;
			}
			if (w == grid.GRID.size() - 1)
			{
				maxW = true;
			}
			if (i == grid.GRID[w].size() - 1)
			{
				maxI = true;
			}

			if (!maxI)
			{
				if (grid.GRID[w][i + 1].getState() == 1)
				{
					neighbors++;
				}
				if (!maxW)
				{
					if (grid.GRID[w + 1][i + 1].getState() == 1)
					{
						neighbors++;
					}
				}
				if (!zeroW)
				{
					if (grid.GRID[w - 1][i + 1].getState() == 1)
					{
						neighbors++;
					}
				}
			}
			if (!maxW)
			{
				if (grid.GRID[w + 1][i].getState() == 1)
				{
					neighbors++;
				}
				if (!zeroI)
				{
					if (grid.GRID[w + 1][i - 1].getState() == 1)
					{
						neighbors++;
					}
				}
			}
			if (!zeroI)
			{
				if (grid.GRID[w][i - 1].getState() == 1)
				{
					neighbors++;
				}
			}
			if (!zeroW)
			{
				if (grid.GRID[w - 1][i].getState() == 1)
				{
					neighbors++;
				}
				if (!zeroI)
				{
					if (grid.GRID[w - 1][i - 1].getState() == 1)
					{
						neighbors++;
					}
				}
			}
			if (neighbors > 3)
			{
				tempGrid[w][i] = 0;
			}
			else if (neighbors < 2)
			{
				tempGrid[w][i] = 0;
			}
			else if (neighbors == 3)
			{
				tempGrid[w][i] = 1;
			}
		}
	}
}

Rules::~Rules()
{
}
