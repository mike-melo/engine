#include <stdio.h>
#include <stdlib.h>

#include "scene.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Scene::Scene() {
  this->numberOfPoints = 0;
  this->numberOfModels = 0;
  this->vao = 0;
}

Scene::~Scene() {
  delete [] models;
}

void Scene::add(Model &_model) {
  //if(models == NULL) {
//     models = new Model[10];
//  }
//  models[numberOfModels] = model;
//  numberOfModels++;
    this->model = _model;
}

void Scene::prepareModel(Model &model) {
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, model.numberOfFaces * 3 * sizeof (float), model.getPoints(), GL_STATIC_DRAW);
  numberOfPoints += model.numberOfFaces * 3;
  printf("\nnumberOfPoints %d", numberOfPoints);
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  //free(model.getPoints());
}

void Scene::prepare() {
  //unsigned int i = 0;
//  for(i=0; i<numberOfModels; i++) {
//    //prepareModel(models[i]);        
//  }
prepareModel(model);
}

void Scene::render() {
  glBindVertexArray (vao);
  glDrawArrays (GL_TRIANGLES, 0, numberOfPoints);  
}
