#ifndef __camera_hpp_
#define __camera_hpp_

#include "math/maths_funcs.h"

class Camera {
            
  public:
  
  float speed;
  float yawSpeed;
  float *position;
  float yaw;
  
  Camera(float speed, float yawSpeed, float *position, float yaw);
  mat4 viewMatrix(); 
  
  void moveLeft(double time);
  void moveRight(double time);
  void moveBack(double time);
  void moveForward(double time);
  void moveUp(double time);
  void moveDown(double time);
  void lookLeft(double time);
  void lookRight(double time);
   
};

#endif
