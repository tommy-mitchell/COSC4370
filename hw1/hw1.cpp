/*******************************************************
 * Homework 1: Rasterization                           *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method you derived in the written portion of the    *
 * homework.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

#define SET_PIXEL(x, y) (image[(x)][(y)] = 1)

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int circleSize;
bool **image;

void renderPixel(int x, int y)
{
	assert(x >= 0 && y >= 0 && x <= circleSize && y <= circleSize);
	
	// TODO:  light up the pixel's symmetric counterpart

	SET_PIXEL(x, y); // render current point
	SET_PIXEL(y, x); // render symmetric point in current quadrant

	/*	uncomment to render entire circle
	SET_PIXEL(y, -x);
	SET_PIXEL(x, -y);
	SET_PIXEL(-x, -y);
	SET_PIXEL(-y, -x);
	SET_PIXEL(-y, x);
	SET_PIXEL(-x, y);
	*/
}

void rasterizeArc(int radius)
{
	// TODO:  rasterize the arc using renderPixel to light up pixels

	int x = 0;
	int y = radius;
	int d = 1 - radius;
	int deltaE = 3;
	int deltaSE = -2 * radius + 5;

	renderPixel(x, y);

	while(y > x)
	{
		if(d < 0) // choose E
		{
			d += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else // choose SE
		{
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;

			y--;
		}

		x++;

		renderPixel(x, y);
	}
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " circleSize\n";
		return 0;
	}
	
#ifdef _WIN32
	sscanf_s(argv[1], "%d", &circleSize);
#else
	sscanf(argv[1], "%d", &circleSize);
#endif
	if (circleSize <= 0) {
		cout << "Image must be of positive size.\n";
		return 0;
	}

	// reserve image as 2d array
	image = new bool*[circleSize+1];
	for (int i = 0; i <= circleSize; i++) image[i] = new bool[circleSize+1];
	
	rasterizeArc(circleSize);

	char filename[50];
#ifdef _WIN32
	sprintf_s(filename, 50, "circle%d.ppm", circleSize);
#else
	sprintf(filename, "circle%d.ppm", circleSize);
#endif

	ofstream outfile(filename);
	outfile << "P3\n# " << filename << "\n";
	outfile << circleSize+1 << ' ' << circleSize+1 << ' ' << 1 << endl;

	for (int i = 0; i <= circleSize; i++)
	for (int j = 0; j <= circleSize; j++)
		outfile << image[circleSize-i][j] << " 0 0\n";
	
	// delete image data
	for (int i = 0; i <= circleSize; i++) delete [] image[i];
	delete [] image;
	
	return 0;
}