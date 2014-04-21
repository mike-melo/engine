#ifndef __model_hpp_
#define __model_hpp_

#include "math/maths_funcs.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_NUM_OF_VERTICES 10

class Model {
      vec4 *vertices;
      unsigned int *vertexOrder;
      size_t numberOfVertices;
      unsigned int numberOfPoints;  
      unsigned int vertexOrderIndex;     
      
      public:
      Model();
      virtual ~Model(); 
        
      static Model *loadObjFile(const char *objFileName);
      float *getPoints();
      unsigned int getNumberOfPoints();  
};

#endif
