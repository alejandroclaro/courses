// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  float angle = degrees * pi/180.0;
  float c = cos(angle);
  float s = sin(angle);
  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  mat3 result = mat3();

  result[0][0] = c + x*x*(1-c);
  result[1][0] = x*y*(1-c)-z*s;
  result[2][0] = x*z*(1-c)+y*s;

  result[0][1] = y*x*(1-c)+z*s;
  result[1][1] = c+y*y*(1-c);
  result[2][1] = y*z*(1-c)-x*s;

  result[0][2] = z*x*(1-c)-y*s;
  result[1][2] = z*y*(1-c)+x*s;
  result[2][2] = c+z*z*(1-c);

  // You will change this return call
  return result;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE
  eye = rotate(degrees, up)*eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE 
  vec3 left = glm::normalize(glm::cross(eye, up));
  mat3 m = rotate(degrees, left);

  eye = m*eye;
  up  = m*up; 
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  vec3 foward = glm::normalize(eye - center);
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

  result[0][3] = -glm::dot(left, eye);
  result[1][3] = -glm::dot(up, eye);
  result[2][3] = -glm::dot(foward, eye);
  result[3][3] = 1.0;

  // You will change this return call
  return result;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 result;
  float rad   = fovy * pi/180.0;
  float scale = 1.0f/tan(rad * 0.5f);

  result[0][0] = scale / aspect;
  result[1][1] = scale;
  result[2][2] = -zFar / (zFar - zNear);
  result[3][3] = 0;
  result[2][3] = -zFar * zNear / (zFar - zNear);
  result[3][2] = -1;

  return result;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 result;

  result[0][0] = sx;
  result[1][1] = sy;
  result[2][2] = sz;
  result[3][3] = 1;

  return result;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 result;

  result[0][0] = 1;
  result[1][1] = 1;
  result[2][2] = 1;
  result[3][3] = 1;

  result[3][0] = tx;
  result[3][1] = ty;
  result[3][2] = tz;

  return result;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
