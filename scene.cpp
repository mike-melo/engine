#include <stdio.h>
#include <stdlib.h>

#include "scene.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Scene::Scene() {
  this->numberOfPoints = 0;
  this->numberOfModels = 0;
}

Scene::~Scene() {
  //delete [] models;
}

void Scene::add(Model *_model) {
  printf("\nAdding model");
  this->models[this->numberOfModels] = *_model;
  numberOfModels++;
  printf("\nAdded model");
}

void Scene::prepareModel(Model *model) {
  printf("\nPreparing model");
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, model->getNumberOfPoints() * sizeof (float), model->getPoints(), GL_STATIC_DRAW);
  this->numberOfPoints += model->getNumberOfPoints();
  unsigned int vao;
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  vaos[numberOfModels] = vao;
}

void Scene::prepare() {
  unsigned int i = 0;
  printf("\nPrepare::numberofModels = %d", numberOfModels);
  for(i=0; i<numberOfModels; i++) {
    prepareModel(&models[i]);        
  }
}

void Scene::render() {
  unsigned int i = 0;
  for(i=0; i<numberOfModels; i++) {
    unsigned int vao = vaos[i];
    glBindVertexArray (vao);
    glDrawArrays (GL_TRIANGLES, 0, numberOfPoints);  
  }
}
