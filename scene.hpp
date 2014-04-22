#ifndef __scene_hpp_
#define __scene_hpp_

#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

class Scene {
  
  private:
  
  Model models[10];
  unsigned int vaos[10];
  unsigned int vao;
  
  Model *model;
  
  //Model models[10];
  unsigned int numberOfModels;
  unsigned int numberOfPoints;
  
  void prepareModel(Model *model);
     
  public:
  
  Scene();
  virtual ~Scene();
  
  void add(Model *model);
  void prepare();
  void render();
  
};

#endif
