#include "transform.h"

using glm::vec3;
using glm::quat;

Transform::Transform(vec3 position, quat orientation) :
    m_position(position), m_orientation(orientation)
{

}

void Transform::rotate(vec3 axis, float angle, const Transform &relativeTo)
{
    axis = relativeTo.orientation() * axis;
    quat q = glm::rotate(quat(1.0f, 0.0f, 0.0f, 0.0f), angle, axis);
    m_position = relativeTo.position() + q * (m_position - relativeTo.position());
    m_orientation *= q;
}


const vec3 & Transform::translate(glm::vec3 translation, const Transform &relativeTo)
{
    return m_position += relativeTo.orientation() * translation;
}

glm::vec3 Transform::toWorldSpace(glm::vec3 v)
{
    return m_position + (m_orientation * v);
}
