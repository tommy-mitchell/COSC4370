#include <iostream>
#include <vector>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Square.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
	cout<<"Generating image..."<<endl;

    Image im(400, 400);

    Scene scene;

    Vector3d point;
	Vector3d color;

	point << 0, 0, 4;
	color << 184, 95, 78;
    scene.addShape(new Sphere(point, 2, color));

	point << -.5, 1, 2.5;
	color << 136, 76, 141;
    scene.addShape(new Sphere(point, .5, color));

	point << .5, 1.25, 2.75;
	color << 31, 157, 55;
    scene.addShape(new Sphere(point, .5, color));

	//point << 1.5, -.5, 2;
	//scene.addShape(new Sphere(point, .75, color, true));

	point << -1, -.5, 1.5;
	color << 125, 112, 94;
	scene.addShape(new Sphere(point, .25, color));

	point << -2.85, -.15, 4.5;
	scene.addShape(new Sphere(point, 1, color));

	/*vector<Vector3d> vertices;
		vertices.push_back(Vector3d(1.5, 0.5, 5));
		vertices.push_back(Vector3d(2.0, 0.5, 5));
		vertices.push_back(Vector3d(2.0, 0.0, 5));
		vertices.push_back(Vector3d(1.5, 0.0, 5));

	scene.addShape(new Square(vertices, color, true));*/

    scene.render(im);

    im.writePNG("test.png");

	cout<<"Image generated."<<endl;
    return 0;
}
