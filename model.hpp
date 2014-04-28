#ifndef __model_hpp_
#define __model_hpp_

#include "math/maths_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Model {
      vector<vec4> vertices;
      vector<int> vertexOrder;
      vector<float> points;
      
      unsigned int vao;
      
      void loadObjFile(const char *objFileName);
      void initPoints();
      
      public:
      Model(const char *fileName);
      virtual ~Model(); 
        
      void prepare();
      void render();  
};

#endif
