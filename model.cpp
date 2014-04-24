#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

Model::Model() {
  this->numberOfPoints = 0;
  //printf("\nCreated model");
}

Model* Model::loadObjFile(const char *objFileName) {
 FILE *stream;
 char line[256];
 vec4 *vertex;
 Model *model = new Model();
 printf("\nNew model is 0x%x", model);
 
 unsigned int newSize = INITIAL_NUM_OF_VERTICES;
 unsigned int v = 0;
 stream = fopen(objFileName, "r");
 
 if(stream == NULL) {
  return NULL;
 }
 printf("\nread stream");
// model->vertexOrderIndex = 0;
 //model->vertexOrder = new unsigned int[3];
 //model->vertices = new 
 //model->vertices = new vec4[newSize];
 //model->vertexOrder = (unsigned int *)malloc(sizeof(unsigned int) * 3);
 //model->vertices = (vec4 *)malloc(sizeof(vec4) * newSize);
 
 do {
  if(line[0] == 'v' && line[1] == ' ') {
   vertex = new vec4();
   //vertex = (vec4 *)calloc(1, sizeof(vec4));
   sscanf(line, "v %f %f %f", &vertex->v[0], &vertex->v[1], &vertex->v[2]);
  // printf("\nhere = %s", objFileName);
   //printf("\nline = %s", line);
   vertex->v[3] = 1;
   model->vertices.push_back(vertex);
   //model->vertices[model->numberOfVertices] = *vertex;
   //model->numberOfVertices++;
   //if(model->numberOfVertices == newSize) {
//    newSize += INITIAL_NUM_OF_VERTICES;
//    //delete [] model->vertices;
//    //model->vertices = new vec4[newSize];
//    model->vertices = (vec4 *)realloc(model->vertices, sizeof(vec4) * newSize);
//   }           
  }  
  if(line[0] == 'f' && line[1] == ' ') {
   unsigned int v0 = 0, v1 = 0, v2 = 0;
   //Have to check when there's only %d//%d"
   sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v0, &v1, &v2);
   
   model->vertexOrder.push_back(v0);
   model->vertexOrder.push_back(v1);
   model->vertexOrder.push_back(v2);
 
 //printf("\nhere face = %s", objFileName);
  // printf("\nline = %s", line);
   //model->vertexOrderIndex += 3;
   //delete[] model->vertexOrder;
   //model->vertexOrder = new unsigned int[model->vertexOrderIndex + 3];
   //model->vertexOrder = (unsigned int *)realloc(model->vertexOrder, sizeof(unsigned int) * (model->vertexOrderIndex + 3));
 
  } 
 } while(fgets(line, 256, stream) != NULL);

 model->numberOfPoints = model->vertexOrder.size() * 3;

 fclose(stream);
 return model;
}

unsigned int Model::getNumberOfPoints() {
  return numberOfPoints;
}

float *Model::getPoints() {
  system("pause");
  printf("\ngetting points");
  float *points = new float[numberOfPoints];
  printf("\nnumber of points = %d", numberOfPoints);
  printf("\ngot points");
  unsigned int i = 0, j = 0;
  //printf("\nvertexOrderIndex = %d, numberOfPoints = %d", vertexOrderIndex, numberOfPoints);
  
  //printf("\nvertexOrder = %d", vertexOrder[i]);
  for(i=0; i<vertexOrder.size(); i++) {
     unsigned int vertexIndex = vertexOrder[i] - 1;
   //printf("\ngetPoints");
  
    points[j++] = vertices[vertexIndex]->v[0];    
    points[j++] = vertices[vertexIndex]->v[1];    
    points[j++] = vertices[vertexIndex]->v[2];   
    printf("\nj = %d, vertexIndex = %d", j, vertexIndex);
  }
  printf("\nread %d points", numberOfPoints);
  return points;
}

Model::~Model() {
     printf("\nDeleting model");
     //free(vertices);
}   
