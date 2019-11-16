#ifndef SHADOW_H
#define SHADOW_H

#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer148
{
	class Shadow
	{
		public:
			static bool isInShadow(HitRecord &r, Vector3d &lightPosition, Scene &scene)
			{
				double offset = .0001;

				Ray shadowRay;

				shadowRay.origin    = r.position + (r.normal * offset);
				shadowRay.direction = lightPosition - shadowRay.origin;

				return isAHit(scene.closestHit(shadowRay));
			}

		private:
			static bool isAHit(HitRecord &r)
			{
				return r.t >= std::numeric_limits<double>::epsilon();
			}
	};
}

#endif