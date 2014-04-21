#include "math/maths_funcs.h"
#include "camera.hpp"
#include "scene.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <math.h>

Camera::Camera(float speed, float yawSpeed, float position[3], float yaw) {
 this->speed = speed;
 this->yawSpeed = yawSpeed;
 this->position = position;
 this->yaw = yaw;
 this->moved = false;
}

void Camera::nextFrame() {
  if (moved) {
    glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, viewMatrix().m);
  }
}

void Camera::roll(int width, int height) {
     #define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
  // input variables    
  float _near = 0.1f; // clipping plane
  float _far = 100.0f; // clipping plane
  float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
  float aspect = (float)width / (float)height; // aspect ratio
  // matrix components
  float range = tan (fov * 0.5f) * _near;
  float Sx = (2.0f * _near) / (range * aspect + range * aspect);
  float Sy = _near / range;
  float Sz = -(_far + _near) / (_far - _near);
  float Pz = -(2.0f * _far * _near) / (_far - _near);  
  
  float proj_mat[] = {
  Sx, 0.0f, 0.0f, 0.0f,
  0.0f, Sy, 0.0f, 0.0f,
  0.0f, 0.0f, Sz, -1.0f,
  0.0f, 0.0f, Pz, 0.0f
  };
  
  const char* vertex_shader =
  "#version 400\n"
  "in vec3 vp;"
  "uniform mat4 view, proj;"
  "void main () {"
  "  gl_Position = proj * view * vec4 (vp, 1.0);"
  "}";

  const char* fragment_shader =
  "#version 400\n"
  "out vec4 frag_colour;"
  "void main () {"
  "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
  "}";
  
  unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 1, &vertex_shader, NULL);
  glCompileShader (vs);
  unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 1, &fragment_shader, NULL);
  glCompileShader (fs);

  shader_programme = glCreateProgram ();
  glAttachShader (shader_programme, fs);
  glAttachShader (shader_programme, vs);
  glLinkProgram (shader_programme);
  
  view_mat_location = glGetUniformLocation (shader_programme, "view");
  glUseProgram (shader_programme);
  glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, viewMatrix().m);
  int proj_mat_location = glGetUniformLocation (shader_programme, "proj");
  glUseProgram (shader_programme);
  glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
}

void Camera::action(Scene *scene) {
  moved = false;
  glUseProgram (shader_programme);
  scene->render();  
}

mat4 Camera::viewMatrix() {
 mat4 T = translate (identity_mat4 (), vec3 (-position[0], -position[1], -position[2]));
 mat4 R = rotate_y_deg (identity_mat4 (), -yaw);
 return R * T;
}

void Camera::moveLeft(double time) {
 this->position[0] -= this->speed * time;
 this->moved = true;
}

void Camera::moveRight(double time) {
 this->position[0] += this->speed * time;
 this->moved = true;
}

void Camera::moveBack(double time) {
 this->position[2] += this->speed * time;
 this->moved = true;
}

void Camera::moveForward(double time) {
 this->position[2] -= this->speed * time;
 this->moved = true;
}

void Camera::moveUp(double time) {
 this->position[1] += this->speed * time;
 this->moved = true;
}

void Camera::moveDown(double time) {
 this->position[1] -= this->speed * time;
 this->moved = true;
}

void Camera::lookLeft(double time) {
 this->yaw += this->yawSpeed * time;
 this->moved = true;
}

void Camera::lookRight(double time) {
 this->yaw -= this->yawSpeed * time;
 this->moved = true;
}
