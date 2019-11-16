#ifndef PHONG_H
#define PHONG_H

#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer148
{
	class Phong
	{
		public:
			static Vector3d getPhongShading(Vector3d &normal, Vector3d &light, Vector3d &objectColor, Vector3d &lightColor, Vector3d &camera)
			{
				Vector3d ambient  = getAmbientLight(lightColor, objectColor);
				Vector3d diffuse  = getDiffuseLight(normal, light, lightColor);
				Vector3d specular = getSpecularlight(camera, normal, light, lightColor);


				return (ambient + diffuse + specular).cwiseProduct(objectColor);
			}

			static Vector3d getAmbientLight(Vector3d& lightColor, Vector3d& objectColor)
			{
				return (AMBIENT_STRENGTH * lightColor).cwiseProduct(objectColor);
			}

			static Vector3d reflect(Vector3d &normal, Vector3d &vector)
			{
				return vector - ( 2 * vector.dot(normal) * normal );
			}

		private:
			static constexpr double  AMBIENT_STRENGTH = .1;
			static constexpr double SPECULAR_STRENGTH = .5;
			static constexpr    int SPECULAR_POWER    = 32;

			static Vector3d getDiffuseLight(Vector3d &normal, Vector3d &light, Vector3d &lightColor)
			{
				return std::max(normal.dot(light), 0.0) * lightColor;
			}

			static Vector3d getSpecularlight(Vector3d &camera, Vector3d &normal, Vector3d &light, Vector3d &lightColor)
			{
				Vector3d reflection = reflect(normal, light);

				return SPECULAR_STRENGTH * std::pow(std::max(camera.dot(reflection), 0.0), SPECULAR_POWER) * lightColor;
			}
	};
}

#endif