#include "math.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace testGame
{
    float getAngle (const vec2& p1, const vec2& p2)
    {
        return atan2(p2.y - p1.y, p2.x - p1.x);
    }

    mat4 translate (const float& x, const float& y)
    {
        return glm::translate(mat4(1.f), vec3(x, y, 0.f));
    }

    mat4 scale (const float& x,const float& y)
    {
        return glm::scale(mat4(1.f), vec3(x, y, 0.f));
    }

    mat4 scale (const float& all)
    {
        return glm::scale(mat4(1.f), vec3(all, all, 0.f));
    }

    mat4 transform (const mat4& translate,
                    const mat4& scale,
                    const mat4& rotation)
    {
        return translate * rotation * scale * mat4(1.f);
    }
}