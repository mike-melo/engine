#include <stdio.h>
#include <stdlib.h>

#include "scene.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

void Scene::add(Model &model) {
  this->models.push_back(model);  
}

void Scene::prepareModel(Model &model) {
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, model.getNumberOfPoints() * sizeof (float), model.getPoints(), GL_STATIC_DRAW); 

  unsigned int vao;
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  vaos.push_back(vao);
}

void Scene::prepare() {
  unsigned int i = 0;
  for(i=0; i<models.size(); i++) {
    prepareModel(models[i]);        
  }
}

void Scene::render() {
  unsigned int i = 0;
  for(i=0; i<vaos.size(); i++) {
    glBindVertexArray (vaos[i]);
    glDrawArrays (GL_TRIANGLES, 0, models[i].getNumberOfPoints());  
  }
}
