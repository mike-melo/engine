#ifndef __scene_hpp_
#define __scene_hpp_

#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"
#include <vector>

using namespace std;

class Scene {
  
  private:
  
  vector<Model> models;
  vector<int> vaos;
  
  void prepareModel(Model &model);
     
  public:
  
  void add(Model &model);
  void prepare();
  void render();
  
};

#endif
