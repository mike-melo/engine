#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

Model::Model() {
  this->numberOfPoints = 0;
}

void Model::toString() {
  unsigned int i=0;
  for(i=0; i<numberOfVertices; i++) {
   printf("x=%lf y=%lf z=%lf, w=%lf\n", vertices[i].v[0], vertices[i].v[1], vertices[i].v[2], vertices[i].v[3]);
  }
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
 
 model->numberOfPoints = 0;
 model->numberOfFaces = 0;
 model->faces = (unsigned int *)malloc(sizeof(unsigned int) * 3);
 model->vertices = (vec4 *)malloc(sizeof(vec4) * newSize);
 
 do {
  if(line[0] == 'v' && line[1] == ' ') {
   vertex = (vec4 *)calloc(1, sizeof(vec4));
   sscanf(line, "v %f %f %f", &vertex->v[0], &vertex->v[1], &vertex->v[2]);
   vertex->v[3] = 1;
   model->vertices[model->numberOfVertices] = *vertex;
   model->numberOfVertices++;
   model->numberOfPoints += 3;
   //printf("line %s\n", line);
   //printf("Vertex %f %f %f\n", vertex->v[0], vertex->v[1], vertex->v[2]);
   //printf("\nRead number of points %d", model->numberOfPoints);
   if(model->numberOfVertices == newSize) {
    newSize += INITIAL_NUM_OF_VERTICES;
    model->vertices = (vec4 *)realloc(model->vertices, sizeof(vec4) * newSize);
    //printf("\nResizing to %d", newSize);
   }           

  }  
  if(line[0] == 'f' && line[1] == ' ') {
     sscanf(line, "f %d//%*d %d//%*d %d//%*d", &model->faces[model->numberOfFaces], &model->faces[model->numberOfFaces + 1], &model->faces[model->numberOfFaces + 2]);
     model->numberOfFaces += 3;
     model->faces = (unsigned int *)realloc(model->faces, sizeof(unsigned int) * (model->numberOfFaces + 3));
     //printf("Face %d %d %d\n",  model->faces[model->numberOfFaces - 3], model->faces[model->numberOfFaces - 2], model->faces[model->numberOfFaces - 1]);
  } 
 } while(fgets(line, 256, stream) != NULL);

 model->numberOfFaces += v;
 
 fclose(stream);
 //fprintf(stderr, "\nRead number of points %d", model->numberOfPoints);
 return model;
}

size_t Model::getNumberOfVertices() {
  return numberOfVertices;      
}

unsigned int Model::getNumberOfPoints() {
  return numberOfPoints;
}


float *Model::getPoints() {
  float *points = new float[numberOfFaces * 3];
  unsigned int i = 0, j = 0;
  //printf("\nNumber of faces = %d", numberOfFaces);
 //printf("\nNumber of vertices = %d", numberOfVertices);
 //system("pause");
  for(i=0; i<numberOfFaces; i++) {
   //printf("\nVertex %f %f %f", vertices[faces[i] - 1].v[0], vertices[faces[i] - 1].v[1], vertices[faces[i] - 1].v[2]);
//     //printf("\nfaces[i] = %d", faces[i]);
     points[j++] = vertices[faces[i] - 1].v[0];
     points[j++] = vertices[faces[i] - 1].v[1];
     points[j++] = vertices[faces[i] - 1].v[2];      
 }
  //for(i=0; i<numberOfVertices; i++) {
//           printf("\nVertex %f %f %f", vertices[i].v[0], vertices[i].v[1], vertices[i].v[2]);
//   points[j] = vertices[i].v[0];
//   j++;
//   points[j] = vertices[i].v[1];
//   j++;
//    points[j] = vertices[i].v[2];
//    j++;
//  }
 // printf("\nGot %d points", j + 1);
  return points;
}

Model::~Model() {
     printf("\nDeleting model");
     //free(vertices);
}   
