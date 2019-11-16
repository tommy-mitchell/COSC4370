#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148
{
	class Sphere : public Shape
	{
		public:
			Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d &color) : c(center), r(radius), Shape(color, false) {}
			Sphere(Eigen::Vector3d& center, double radius, Eigen::Vector3d& color, bool isReflective) : c(center), r(radius), Shape(color, isReflective) {}

			virtual HitRecord intersect(const Ray &ray);

		private:
			Eigen::Vector3d c;
			double          r;
	};
}

#endif