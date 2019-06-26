#include "transform.h"

using glm::sin;
using glm::cos;
using glm::normalize;
using glm::vec3;
using glm::quat;

vec3 quaternionToVec3(quat q)
{
    return vec3(q.x, q.y, q.z);
}

Transform::Transform(vec3 position, quat orientation) :
    m_position(position), m_orientation(orientation),
    m_transformationMatrix(1.0f)
{
    _recalculateTransformationMatrix();
}

void Transform::rotate(vec3 axis, float angle, Space relativeTo)
{
    m_orientation = glm::rotate(m_orientation, angle, axis);
    _recalculateTransformationMatrix();
}

void Transform::translate(glm::vec3 translation, Space relativeTo)
{
    m_position += translation;
    _recalculateTransformationMatrix();
}

void Transform::_recalculateTransformationMatrix()
{
    m_transformationMatrix = glm::translate(m_transformationMatrix, m_position);
    m_transformationMatrix *= glm::toMat4(m_orientation);
}

glm::vec3 Transform::toWorldOrientation(glm::vec3 vec) {
    return glm::toMat3(m_orientation) * vec;
}
