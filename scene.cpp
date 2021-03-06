#include <stdio.h>
#include <stdlib.h>

#include "scene.hpp"

void Scene::add(Model &model) {
  this->models.push_back(model);  
}

void Scene::prepare() {
  unsigned int i = 0;
  for(i=0; i<models.size(); i++) {
    models[i].prepare();         
  }
}

void Scene::render() {
  unsigned int i = 0;
  for(i=0; i<models.size(); i++) {
    models[i].render(); 
  }
}
