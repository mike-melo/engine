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
               
  size_t numberOfPoints;
  unsigned int vao;
  
  void prepareModel(Model model);
     
  public:
  
  Scene(float points[], size_t numberOfPoints);
  virtual ~Scene();
  
  void add(Model model);
  void prepare();
  void render();
  
};

#endif
