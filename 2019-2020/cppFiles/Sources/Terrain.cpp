#include "../Headers/Terrain.h"

#include <iostream>
#include <fstream>

bool isValidPoint(double x, double y, terrain* grid) {
	if(x >= grid->width || x < 0 || y >= grid->height || y < 0)
		return false;
	if(grid->grid[(int)x][(int)y] > 0)
		return false;
    return true; 
}

bool isValidEdgePoint(double x, double y, terrain* grid, int hole) {
	if(x >= grid->width || x < 0 || y >= grid->height || y < 0)
		return false;
	if(grid->grid[(int)x][(int)y] == 1 || (hole == 0 && grid->grid[(int)x][(int)y] == 2))
		return false;
    return true; 
}

void addRock(terrain* grid, int x, int y) {
	for(int i = x - 5; i < x + 6; i++) {
		for(int j = y - 5; j < y + 6; j++) {
			if(x >= 0 && y >= 0 && x < 100 && y < 100)
				grid->grid[i][j] = 1;
		}
	}
}

void addHole(terrain* grid, int x, int y) {
	for(int i = x - 5; i < x + 6; i++) {
		for(int j = y - 5; j < y + 6; j++) {
			if(x >= 0 && y >= 0 && x < 100 && y < 100)
				grid->grid[i][j] = 2;
		}
	}
	for(int i = x - 1; i < x + 2; i++) {
		for(int j = y - 1; j < y + 2; j++) {
			if(x >= 0 && y >= 0 && x < 100 && y < 100)
				grid->grid[i][j] = -1;
		}
	}
}

void readFile(terrain* grid) {
	std::ifstream file("obstacles");
	int a, b, c;
	while(file >> a >> b >> c) {
		if(c == 1)
			addRock(grid, a, b);
		if(c == 2)
			addHole(grid, a, b);
	}
}

terrain* buildTerrain(int** field) {
	terrain* grid = new terrain;
	grid->width = WIDTH;
	grid->height = HEIGHT;
	for(int i = 0; i < WIDTH; i++) {
	    for(int j = 0; j < HEIGHT; j++) {
		if(field[i][j] == 0)
		    grid->grid[i][j] = 0;
		else if(field[i][j] == 1)
		    addRock(grid, i, j);
		else if(field[i][j] == 2)
		    addHole(grid, i, j);
	    }
	}

	//readFile(grid);

	return grid;
}
