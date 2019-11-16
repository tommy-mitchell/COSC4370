#include "Scene.h"
#include "Phong.h"
#include "Shadow.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int depth) {
	Vector3d result;
	result << 0, 0, 0;
	
	if(depth > MAX_DEPTH) return result;

    HitRecord r = closestHit(ray);

    if(r.t < numeric_limits<double>::epsilon()) return result;

	Vector3d cameraPos = Vector3d(0.0, 0.0, 0.0);

    Vector3d lightDir  = (lightPos  - r.position).normalized();
	Vector3d cameraDir = (cameraPos - r.position).normalized();

	if(r.isReflective)
	{
		Ray reflectRay;

		reflectRay.origin    = r.position + (r.normal * .0001);
		reflectRay.direction = Phong::reflect(r.normal, (Vector3d) ray.direction);

		result += .8 * trace(reflectRay, depth + 1);
	}
	else // diffuse
	{
		if(Shadow::isInShadow(r, lightPos, *this))
			return Phong::getAmbientLight(Vector3d(1.0, 1.0, 1.0), r.objColor);
	
		result = Phong::getPhongShading(r.normal, lightDir, r.objColor, Vector3d(1.0, 1.0, 1.0), cameraDir);
	}

	return result;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay, 0);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}
