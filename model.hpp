#ifndef __model_hpp_
#define __model_hpp_

#include "math/maths_funcs.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_NUM_OF_VERTICES 10

class Model {
      vec4 *vertices;
      unsigned int *faces;
      size_t numberOfVertices;
      unsigned int numberOfPoints;
     
            
      public:
      Model();
       unsigned int numberOfFaces;
      static Model *loadObjFile(const char *objFileName);
      float *getPoints();
      void toString();
      size_t getNumberOfVertices();
      unsigned int getNumberOfPoints();
      
      virtual ~Model();    
};

#endif
