#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

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

 this->numberOfPoints = this->vertexOrder.size() * 3;

 fclose(stream);
}

unsigned int Model::getNumberOfPoints() {
  return numberOfPoints;
}

float *Model::getPoints() {
  float *points = new float[numberOfPoints];
  unsigned int i = 0, j = 0;

  for(i=0; i<vertexOrder.size(); i++) {
    unsigned int vertexIndex = vertexOrder[i] - 1;
  
    points[j++] = vertices[vertexIndex].v[0];    
    points[j++] = vertices[vertexIndex].v[1];    
    points[j++] = vertices[vertexIndex].v[2];   
  }
 
  return points;
}

Model::~Model() {
}   

