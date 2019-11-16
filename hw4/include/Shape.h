#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

namespace Raytracer148
{
	struct Ray
	{
		Eigen::Vector3d origin, direction;
	};

	class Shape;

	struct HitRecord
	{
		Eigen::Vector3d position, normal, objColor;
		double t;
		bool isReflective;
	};

	class Shape
	{
		public:
			Shape(Eigen::Vector3d &color, bool surfaceIsReflective) : col(color / 255), isReflective(surfaceIsReflective) {}
			virtual ~Shape(){}
			virtual HitRecord intersect(const Ray &ray) = 0;
		protected:
			Eigen::Vector3d col;
			bool isReflective;
	};
}

#endif