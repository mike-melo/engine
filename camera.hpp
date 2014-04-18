#ifndef __camera_hpp_
#define __camera_hpp_

#include "scene.hpp"
#include "math/maths_funcs.h"

class Camera {
      
  float speed;
  float yawSpeed;
  float *position;
  float yaw;
  bool moved;
  
  int view_mat_location;
  unsigned int shader_programme;
  
  mat4 viewMatrix(); 
            
  public:
  
  Camera(float speed, float yawSpeed, float *position, float yaw);
  
  void roll(int width, int height);
  void action(Scene *scene);
  void nextFrame();
  
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
