#ifndef __scene_hpp_
#define __scene_hpp_

#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

class Scene {
  
  private:
  
  unsigned int *vaos;
  
  Model model;
  
  Model *models;
  size_t numberOfModels;
               
  unsigned int numberOfPoints;
  unsigned int vao;
  
  void prepareModel(Model &model);
     
  public:
  
  Scene();
  virtual ~Scene();
  
  void add(Model &model);
  void prepare();
  void render();
  
};

#endif
