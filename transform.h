#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);
const glm::quat IDENTITY_QUATERNION(1.0f, 0.0f, 0.0f, 0.0f);

class Transform
{
public:
    Transform(glm::vec3 position = glm::vec3(), glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    inline void setPosition(glm::vec3 position) {m_position = position;}
    inline void setOrientation(glm::quat orientation) {m_orientation = orientation;}

    void rotate(glm::vec3 axis, float angle, const Transform &relativeTo);
    inline void rotate(glm::vec3 axis, float angle) {m_orientation = glm::rotate(m_orientation, angle, axis);}
    inline void rotate(glm::vec3 euler, const Transform &relativeTo) {rotateAround(relativeTo.position(), glm::quat(euler));}
    inline void rotate(glm::vec3 euler) {m_orientation *= glm::quat(euler);}
    void rotateAround(glm::vec3 point, glm::quat quaternion);

    const glm::vec3 & translate(glm::vec3 translation, const Transform &relativeTo);
    inline const glm::vec3 & translate(glm::vec3 translation) {return translate(translation, *this);}

    inline const glm::vec3 & position() const {return m_position;}
    inline const glm::quat & orientation() const {return m_orientation;}

    inline void addChild(std::unique_ptr<Transform> &child)  {child->setParent(this);m_children.push_back(std::move(child));}
    inline const std::vector<std::unique_ptr<Transform>> & children() const {return m_children;}

    inline void setParent(Transform *parent) {m_parent = parent;}
    inline Transform const * parent() const {return m_parent;}

    glm::mat4 getWorldTransformationMatrix() const;

private:
    glm::vec3 m_position;
    glm::quat m_orientation;

    Transform *m_parent = nullptr;

    std::vector<std::unique_ptr<Transform>> m_children;
};

#endif // TRANSFORM_H
