#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  
  // output reflected ray direction
  Eigen::Vector3d r;
  r = in - 2 * (in.dot(n)) * n;
  r.normalized();
  
  return r;
  
  ////////////////////////////////////////////////////////////////////////////
}
