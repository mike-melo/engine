#include "math/maths_funcs.h"
#include "camera.hpp"

#include <stdio.h>

Camera::Camera(float _speed, float _yawSpeed, float _position[3], float _yaw) {
 speed = _speed;
 yawSpeed = _yawSpeed;
 position = _position;
 yaw = _yaw;
 printf("\nspeed = %f", speed);
 printf("\nyawSpeed = %f", yawSpeed);
 printf("\nposition = %f %f %f", position[0], position[1], position[2]);
 printf("\nyaw = %f", yaw);
}

mat4 Camera::viewMatrix() {
printf("\nspeed = %f", speed);
 printf("\nyawSpeed = %f", yawSpeed);
 printf("\nposition = %f %f %f", position[0], position[1], position[2]);
 printf("\nyaw = %f", yaw);
 mat4 T = translate (identity_mat4 (), vec3 (-position[0], -position[1], -position[2]));
 mat4 R = rotate_y_deg (identity_mat4 (), -yaw);
 mat4 RESULT = R * T;
 printf("\nT = %f", T.m);
 printf("\nR = %f", R.m);
 printf("\nviewMatrix = %f", RESULT.m);
 return RESULT;
}

void Camera::moveLeft(double time) {
 position[0] -= speed * time;
}

void Camera::moveRight(double time) {
 position[0] += speed * time;
}

void Camera::moveBack(double time) {
 position[2] += speed * time;
}

void Camera::moveForward(double time) {
 position[2] -= speed * time;
}

void Camera::moveUp(double time) {
 position[1] += speed * time;
}

void Camera::moveDown(double time) {
 position[1] -= speed * time;
}

void Camera::lookLeft(double time) {
 yaw += yawSpeed * time;
}

void Camera::lookRight(double time) {
 yaw -= yawSpeed * time;
}
