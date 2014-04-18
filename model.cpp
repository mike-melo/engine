#include <stdio.h>
#include <stdlib.h>

#include "model.hpp"

Model::Model() {
}

void Model::toString() {
  unsigned int i=0;
  for(i=0; i<numberOfVertices; i++) {
   printf("x=%lf y=%lf z=%lf, w=%lf\n", vertices[i]->v[0], vertices[i]->v[1], vertices[i]->v[2], vertices[i]->v[3]);
  }
}

Model* Model::loadObjFile(const char *objFileName) {
 FILE *stream;
 char line[256];
 vec4 *vertex;
 Model *model = new Model();
 unsigned int newSize = INITIAL_NUM_OF_VERTICES;

 stream = fopen(objFileName, "r");
 
 if(stream == NULL) {
  return NULL;
 }
 
 model->vertices = (vec4 **)malloc(sizeof(vec4 *) * newSize);
 
 do {
  if(line[0] == 'v' && line[1] == ' ') {
   vertex = (vec4 *)calloc(1, sizeof(vec4));
   sscanf(line, "v %lf %lf %lf", &vertex->v[0], &vertex->v[1], &vertex->v[2]);
   vertex->v[3] = 1;
   model->vertices[model->numberOfVertices] = vertex;
   model->numberOfVertices++;
   if(model->numberOfVertices == newSize) {
    newSize += INITIAL_NUM_OF_VERTICES;
    model->vertices = (vec4 **)realloc(model->vertices, sizeof(vec4 *) * newSize);
   }

  }   
 } while(fgets(line, 256, stream) != NULL);

 
 fclose(stream);
 
 return model;
}

Model::~Model() {
     int i;
     for(i=0; i<numberOfVertices; i++) {
      free(vertices[i]);
     }
     free(vertices);
}   
