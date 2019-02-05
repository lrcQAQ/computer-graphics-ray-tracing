#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  
  // initialize ray color rgb
  rgb = Eigen::Vector3d(0,0,0);
  
  // initialize variables and find hit
  int hit_id; double t; Eigen::Vector3d n;
  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);
  
  // ray hits an object
  if(hit){
    
    // evaluate shading
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    
    // limited numebr of reflect depths
    if(num_recursive_calls < 5){
      
      // reflection ray
      Ray ref_ray; Eigen::Vector3d ref_rgb;
      ref_ray.origin = ray.origin + t * ray.direction;
      ref_ray.direction = reflect(ray.direction, n);
      
      // recursively find rgb for such reflection ray
      raycolor(ref_ray, 0.0001, objects, lights, num_recursive_calls + 1, ref_rgb);
      
      // mirror reflection
      Eigen::Vector3d km = objects[hit_id]->material->km;
      rgb += (km.array() * ref_rgb.array()).matrix();
      
    }
    return true;
  }
  else{
    return false;
  }
  
  ////////////////////////////////////////////////////////////////////////////
}
