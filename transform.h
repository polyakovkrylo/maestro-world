#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
    Transform(glm::vec3 position = glm::vec3(), glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    inline void setPosition(glm::vec3 position) {m_position = position;}
    inline void setOrientation(glm::quat orientation) {m_orientation = orientation;}

    void rotate(glm::vec3 axis, float angle, const Transform &relativeTo);
    inline void rotate(glm::vec3 axis, float angle) {m_orientation = glm::rotate(m_orientation, angle, axis);}
    void rotateAround(glm::vec3 point, glm::quat quaternion);

    const glm::vec3 & translate(glm::vec3 translation, const Transform &relativeTo);
    inline const glm::vec3 & translate(glm::vec3 translation) {return translate(translation, *this);}

    inline const glm::vec3 & position() const {return m_position;}
    inline const glm::quat & orientation() const {return m_orientation;}

    glm::vec3 toWorldSpace(glm::vec3 v);

private:
    glm::vec3 m_position;
    glm::quat m_orientation;
};

#endif // TRANSFORM_H
