// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
  float angle = degrees * pi/180.0;
  float c = cos(angle);
  float s = sin(angle);
  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  mat3 result = mat3();

  result[0][0] = c + x*x*(1-c);
  result[0][1] = x*y*(1-c)-z*s;
  result[0][2] = x*z*(1-c)+y*s;

  result[1][0] = y*x*(1-c)+z*s;
  result[1][1] = c+y*y*(1-c);
  result[1][2] = y*z*(1-c)-x*s;

  result[2][0] = z*x*(1-c)-y*s;
  result[2][1] = z*y*(1-c)+x*s;
  result[2][2] = c+z*z*(1-c);

  // You will change this return call
  return result;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
  eye = eye*rotate(degrees, up);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
  vec3 left = glm::normalize(glm::cross(eye, up));
  mat3 m = rotate(degrees, left);

  eye = eye*m;
  up  = up*m;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
  vec3 foward = glm::normalize(eye);
  vec3 left = glm::normalize(glm::cross(up, eye));
  //up = glm::normalize(glm::cross(left, eye));

  mat4 result;

  result[0][0] = left[0];
  result[1][0] = up[0];
  result[2][0] = foward[0];
  result[3][0] = 0.0;

  result[0][1] = left[1];
  result[1][1] = up[1];
  result[2][1] = foward[1];
  result[3][1] = 0.0;

  result[0][2] = left[2];
  result[1][2] = up[2];
  result[2][2] = foward[2];
  result[3][2] = 0.0;

  result[0][3] = -0.2*glm::dot(left, eye);
  result[1][3] = -0.2*glm::dot(up, eye);
  result[2][3] = -0.2*glm::dot(eye, eye);
  result[3][3] = 1.0;

  // You will change this return call
  return result;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
