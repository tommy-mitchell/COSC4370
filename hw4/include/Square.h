#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"
#include <vector>

namespace Raytracer148
{
	class Square : public Shape
	{
		public:
			Square(std::vector<Eigen::Vector3d> &verts, Eigen::Vector3d &color) : vertices(verts), Shape(color, false) {}
			Square(std::vector<Eigen::Vector3d> &verts, Eigen::Vector3d &color, bool isReflective) : vertices(verts), Shape(color, isReflective) {}

			virtual HitRecord intersect(const Ray &ray);

		private:
			std::vector<Eigen::Vector3d> vertices;

			HitRecord intersectPlane(const Ray &ray, Eigen::Vector3d &n, Eigen::Vector3d &q);
	};
}

#endif