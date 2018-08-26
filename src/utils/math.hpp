#ifndef __MATH_HPP__
#define __MATH_HPP__

#include <glm/gtc/matrix_transform.hpp>

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using mat4 = glm::mat4;

float getAngle  (const vec2& p1, const vec2& p2);
mat4 translate  (const float& x, const float& y);
mat4 scale      (const float& x, const float& y);
mat4 scale      (const float& all);
mat4 transform  (const mat4& translate, const mat4& scale = mat4(1.f),
                 const mat4& rotation = mat4(1.f));

#endif //!__MATH_HPP__