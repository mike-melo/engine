#ifndef __scene_hpp_
#define __scene_hpp_

#include <stdio.h>
#include <stdlib.h>

class Scene {
  
  private:
                 
  float *points;   
  size_t numberOfPoints;
  unsigned int vao;
     
  public:
  
  Scene(float points[], size_t numberOfPoints);
  void prepare();
  void render();
  
};

#endif
