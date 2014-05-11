#ifndef __model_hpp_
#define __model_hpp_

#include "math/maths_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class Model {
      vector<float> points;
      
      unsigned int vao;
      
      void load(const std::string& modelFileName);
      
      public:
      Model(const std::string& modelFileName);
      virtual ~Model(); 
        
      void prepare();
      void render();  
};

#endif
