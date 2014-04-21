#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

Model::Model() {
  this->numberOfPoints = 0;
}

Model* Model::loadObjFile(const char *objFileName) {
 FILE *stream;
 char line[256];
 vec4 *vertex;
 Model *model = new Model();
 unsigned int newSize = INITIAL_NUM_OF_VERTICES;
 unsigned int v = 0;
 stream = fopen(objFileName, "r");
 
 if(stream == NULL) {
  return NULL;
 }
 
 model->vertexOrderIndex = 0;
 model->vertexOrder = (unsigned int *)malloc(sizeof(unsigned int) * 3);
 model->vertices = (vec4 *)malloc(sizeof(vec4) * newSize);
 
 do {
  if(line[0] == 'v' && line[1] == ' ') {
   vertex = (vec4 *)calloc(1, sizeof(vec4));
   sscanf(line, "v %f %f %f", &vertex->v[0], &vertex->v[1], &vertex->v[2]);
   vertex->v[3] = 1;
   model->vertices[model->numberOfVertices] = *vertex;
   model->numberOfVertices++;
   if(model->numberOfVertices == newSize) {
    newSize += INITIAL_NUM_OF_VERTICES;
    model->vertices = (vec4 *)realloc(model->vertices, sizeof(vec4) * newSize);
   }           
  }  
  if(line[0] == 'f' && line[1] == ' ') {
   //Have to check when there's only %d//%d"
   sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &model->vertexOrder[model->vertexOrderIndex], &model->vertexOrder[model->vertexOrderIndex + 1], &model->vertexOrder[model->vertexOrderIndex + 2]);
   model->vertexOrderIndex += 3;
   model->vertexOrder = (unsigned int *)realloc(model->vertexOrder, sizeof(unsigned int) * (model->vertexOrderIndex + 3));
  } 
 } while(fgets(line, 256, stream) != NULL);

 model->numberOfPoints = model->vertexOrderIndex * 3;

 fclose(stream);
 return model;
}

unsigned int Model::getNumberOfPoints() {
  return numberOfPoints;
}

float *Model::getPoints() {
  float *points = new float[numberOfPoints];
  unsigned int i = 0, j = 0;
  for(i=0; i<vertexOrderIndex; i++) {
    unsigned int vertexIndex = vertexOrder[i] - 1;
   
    points[j++] = vertices[vertexIndex].v[0];    
    points[j++] = vertices[vertexIndex].v[1];    
    points[j++] = vertices[vertexIndex].v[2];   
  }
  return points;
}

Model::~Model() {
     printf("\nDeleting model");
     //free(vertices);
}   
