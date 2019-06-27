#include "transform.h"

using glm::vec3;
using glm::quat;

Transform::Transform(vec3 position, quat orientation) :
    m_position(position), m_orientation(orientation)
{

}

void Transform::rotate(vec3 axis, float angle, const Transform &relativeTo)
{
    quat q = glm::rotate(quat(1.0f, 0.0f, 0.0f, 0.0f),
                         angle,
                         relativeTo.orientation() * axis);

    rotateAround(relativeTo.position(), q);
}

void Transform::rotateAround(vec3 point, quat quaternion)
{
    m_position = point + quaternion * (m_position - point);
    m_orientation *= quaternion;
}


const vec3 & Transform::translate(vec3 translation, const Transform &relativeTo)
{
    return m_position += relativeTo.orientation() * translation;
}

glm::mat4 Transform::getWorldTransformationMatrix() const{
    glm::mat4 transformationMatrix = glm::translate(glm::toMat4(m_orientation), m_position);

    if (m_parent != nullptr) {
        transformationMatrix = m_parent->getWorldTransformationMatrix() * transformationMatrix;
    }

    return transformationMatrix;
}
