#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  
  // initialize rgb and material characteristics
  Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d ka = objects[hit_id]->material->ka;  
  Eigen::Vector3d kd = objects[hit_id]->material->kd;  
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  double phong_exp = objects[hit_id]->material->phong_exponent;
  
  // ambient shading
  rgb = ka * 0.1;
  
  Eigen::Vector3d p = ray.origin + t * ray.direction;
  p.normalized();
  
  for(int i=0; i<lights.size(); i++){
    
    Eigen::Vector3d l; double max_t;
    Eigen::Vector3d I = lights[i]->I;
    lights[i]->direction(p, l, max_t);
    l.normalized();
    
    // the ray from p to light
    Ray light;
    light.origin = p;
    light.direction = l;
    
    int l_id; double l_t; Eigen::Vector3d l_n;
    // check p in shadow
    if(!first_hit(light, 0.0001, objects, l_id, l_t, l_n) || l_t >= max_t){
      // half vector h
      Eigen::Vector3d h = ((-ray.direction).normalized() + l.normalized()).normalized();
      
      // add diffuse
      rgb = rgb + (kd.array()*I.array()*fmax(n.dot(l), 0)).matrix();
      // add specular
      rgb = rgb + (ks.array()*I.array()*pow(fmax(n.dot(h), 0), phong_exp)).matrix();
    
    }
  }
  
  return rgb;
  
  ////////////////////////////////////////////////////////////////////////////
}
