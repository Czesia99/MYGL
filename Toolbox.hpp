#pragma once

#include "glm/detail/type_vec4.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include <chrono>

namespace mygl
{
    void extractPlanesFromProjectionViewMatrix(const glm::mat4& m, glm::vec4 planes[6]);
    void startChrono();
    void stopChrono();
}