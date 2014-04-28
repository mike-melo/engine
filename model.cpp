#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

#include "GL/glew.h"

using namespace std;

Model::Model(const char *objFileName) {            
  this->loadObjFile(objFileName);
}

void Model::loadObjFile(const char *objFileName) {
 FILE * stream = fopen(objFileName, "r");
 
 if(stream == NULL) {
  throw "could not open load file";
 }
 
 char line[256];
 
 do {
  if(line[0] == 'v' && line[1] == ' ') {
   vec4 vertex = vec4();
   sscanf(line, "v %f %f %f", &vertex.v[0], &vertex.v[1], &vertex.v[2]);
   vertex.v[3] = 1;
   this->vertices.push_back(vertex);       
  }  
  
  if(line[0] == 'f' && line[1] == ' ') {
   unsigned int v0 = 0, v1 = 0, v2 = 0;
   //Have to check when there's only %d//%d"
   sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v0, &v1, &v2);
   
   this->vertexOrder.push_back(v0);
   this->vertexOrder.push_back(v1);
   this->vertexOrder.push_back(v2);
  } 
 } while(fgets(line, 256, stream) != NULL);

 initPoints();
 
 fclose(stream);
}

void Model::prepare() {
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);

  glBufferData (GL_ARRAY_BUFFER, this->points.size() * sizeof (float), &this->points.front(), GL_STATIC_DRAW); 

  glGenVertexArrays (1, &this->vao);
  glBindVertexArray (this->vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Model::render() {
  glBindVertexArray (this->vao);
  glDrawArrays (GL_TRIANGLES, 0, this->points.size());     
}

void Model::initPoints() {
  for(unsigned int i=0; i<vertexOrder.size(); i++) {
    unsigned int vertexIndex = vertexOrder[i] - 1;
    this->points.push_back(vertices[vertexIndex].v[0]);
    this->points.push_back(vertices[vertexIndex].v[1]);
    this->points.push_back(vertices[vertexIndex].v[2]);
  }      
}

Model::~Model() {
}   

