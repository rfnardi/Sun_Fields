#include <iostream>
#include "heliostato.h"
#include "bare_functions.h"
/* #include "./heliostato.cpp" */

int
main ()
{
//Heliostato::Heliostato()
  Heliostato result1;
  std::cout << "Coordenada x: " << result1.base_pos.coord[0] << std::endl;
  std::cout << "Coordenada y: " << result1.base_pos.coord[1] << std::endl;
  std::cout << "Coordenada z: " << result1.base_pos.coord[2] << std::endl;

  std::
    cout <<
    "******************************************************************************" << std::endl;;
    std::cout<<"set_normal"<< std::endl;
    
    vetor_3d sun_pos(01,02,40);
    vetor_3d focus_pos(12,43,5);
    
  Heliostato h1;
  
  h1.set_normal(sun_pos, focus_pos);
    
  std::
    cout <<
    "******************************************************************************" << std::endl;;
    
  
  vetor_3d base_pos (20, 20, 0);
  float vert_axis_height = 1.5;
  float mirror_height = 2.0;
  float mirror_width = 2.0;

  Heliostato h (base_pos, vert_axis_height, mirror_height, mirror_width);

  vetor_3d result (0, 0, 0);
  vetor_3d result2 (0, 0, 0);

 // h.set_point_inside_mirror_region (0.2, 0.5);
std::
    cout <<
    "******************************************************************************" << std::endl;;
std::cout<<"pick_point_inside_mirror_region:"<< std::endl;
  result = h.pick_point_inside_mirror_region (0.1, 0.3, result);
  std::cout << "Coordenada x: " << result.coord[0] << std::endl;
  std::cout << "Coordenada y: " << result.coord[1] << std::endl;
  std::cout << "Coordenada z: " << result.coord[2] << std::endl;
  
  std::
    cout <<
    "******************************************************************************" << std::endl;;
    std::cout<<"intersec_plano_reta:"<< std::endl;
    
   //result2 = h.intersec_plano_reta(pick_point_inside_mirror_region,result);
  std::cout << "Coordenada x: " << result2.coord[0] << std::endl;
  std::cout << "Coordenada y: " << result2.coord[1] << std::endl;
  std::cout << "Coordenada z: " << result2.coord[2] << std::endl;
  return 0;
}
