#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  
  // from point towards light
  d = (p - q).normalized();
  // parametric distance
  max_t = (p - q).norm();
  
  ////////////////////////////////////////////////////////////////////////////
}
