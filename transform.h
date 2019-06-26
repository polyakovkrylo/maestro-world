#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

const glm::vec3 UP = {0.0f, 0.0f, 1.0f};
const glm::vec3 LEFT = {0.0f, 1.0f, 0.0f};
const glm::vec3 FORWARD = {1.0f, 0.0f, 0.0f};

enum Space {
    WorldSpace,
    ObjectSpace
};

class Transform
{
public:
    Transform(glm::vec3 position = glm::vec3(), glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    inline void setPosition(glm::vec3 position) {m_position = position;}
    inline void setOrientation(glm::quat orientation) {m_orientation = orientation;}
    void rotate(glm::vec3 axis, float angle);
    void translate(glm::vec3 translation);

    inline const glm::vec3 & position() const {return m_position;}
    inline const glm::quat & orientation() const {return m_orientation;}

    inline glm::vec3 up() {return toWorldOrientation(UP);}
    inline glm::vec3 left() {return toWorldOrientation(LEFT);}
    inline glm::vec3 forward() {return toWorldOrientation(FORWARD);}
    inline glm::mat4 transformationMatrix() {return m_transformationMatrix;}

    glm::vec3 toWorldOrientation(glm::vec3 vec);

private:
    glm::vec3 m_position;
    glm::quat m_orientation;
    glm::mat4 m_transformationMatrix;

    void _recalculateTransformationMatrix();
};

#endif // TRANSFORM_H
