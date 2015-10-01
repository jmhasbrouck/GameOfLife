#pragma once
#include "Grid.h"
#include <vector>
#include "Button.h"
class Rules
{
public:
	Rules();
	~Rules();
	void Check(Grid &grid);
	void liveordie(Grid& grid);
private:
	int x, y;
	vector<vector<bool>> tempGrid;
	vector<bool> temp;
};

