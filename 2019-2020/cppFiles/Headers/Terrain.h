static const int WIDTH = 100;
static const int HEIGHT = 100;

struct terrain {
	int grid [WIDTH][HEIGHT];
	int width;
	int height;
};

bool isValidPoint(double x, double y, terrain* grid);
bool isValidEdgePoint(double x, double y, terrain* grid, int hole);
terrain* buildTerrain(int** field);
