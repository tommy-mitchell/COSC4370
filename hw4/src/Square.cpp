#include "Square.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Square::intersect(const Ray &ray)
{
	//HitRecord result;

	Vector3d normal = (vertices[2] - vertices[1]).cross(vertices[0] - vertices[1]);
	Vector3d pointQ = vertices[0];

	HitRecord result = intersectPlane(ray, normal, pointQ);



	result.objColor		= col;
	result.isReflective = isReflective;

	return result;
}

HitRecord Square::intersectPlane(const Ray &ray, Eigen::Vector3d &n, Eigen::Vector3d &q)
{
	HitRecord result;

	result.t = ( n.dot(q - ray.origin) ) / ( n.dot(ray.direction) );

	if(result.t < 0) return result; // no hit

	if(n.dot(ray.direction) == 0) return result; // plane parallel -> no hit

	result.position	= ray.origin + result.t * ray.direction;
	result.normal	= (result.position - q).normalized();
	
	return result;
}

//bool isPolygonInPlane()