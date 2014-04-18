#ifndef __model_hpp_
#define __model_hpp_

#include "math/maths_funcs.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_NUM_OF_VERTICES  10

class Model {
      vec4 **vertices;
      size_t numberOfVertices;

      Model();
            
      public:
     
      static Model *loadObjFile(const char *objFileName);

      void toString();
      
      virtual ~Model();    
};

#endif
