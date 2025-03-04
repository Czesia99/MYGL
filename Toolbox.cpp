#include "Toolbox.hpp"
#include "glm/glm.hpp"

namespace mygl
{
    void extractPlanesFromProjectionViewMatrix(const glm::mat4& m, glm::vec4 planes[6])
    {
        for (int i = 4; i--; ) { planes[0][i] = m[i][3] + m[i][0]; } // left
        for (int i = 4; i--; ) { planes[1][i] = m[i][3] - m[i][0]; } // right
        for (int i = 4; i--; ) { planes[2][i] = m[i][3] + m[i][1]; } // bottom
        for (int i = 4; i--; ) { planes[3][i] = m[i][3] - m[i][1]; } // top
        for (int i = 4; i--; ) { planes[4][i] = m[i][3] + m[i][2]; } // near
        for (int i = 4; i--; ) { planes[5][i] = m[i][3] - m[i][2]; } // far
    }
}