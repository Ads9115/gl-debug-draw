#include "DebugDraw.h"
#include <glm/glm.hpp>


namespace DebugDraw
{
    void Init() {}
    void Shutdown() {}
    void BeginFrame() {}
    void EndFrame(const glm::mat4& viewProj) {}
    void DrawLine(
        const glm::vec3& start,
        const glm::vec3& end,
        const glm::vec3& color) {
    }
}
