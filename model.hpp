#ifndef __model_hpp_
#define __model_hpp_

#include "math/maths_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#define INITIAL_NUM_OF_VERTICES 10

class Model {
      vector<vec4*> vertices;
      vector<int> vertexOrder;
      
      unsigned int numberOfPoints;       
      
      public:
      Model();
      virtual ~Model(); 
        
      static Model *loadObjFile(const char *objFileName);
      float *getPoints();
      unsigned int getNumberOfPoints();  
};

#endif
