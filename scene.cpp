#include <stdio.h>
#include <stdlib.h>

#include "scene.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Scene::Scene(float _points[], size_t _numberOfPoints) {
  points = _points;
  numberOfPoints = _numberOfPoints;
  vao = 0;
}

void Scene::prepare() {
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, numberOfPoints * sizeof (float), points, GL_STATIC_DRAW);
  
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Scene::render() {
  glBindVertexArray (vao);
}
