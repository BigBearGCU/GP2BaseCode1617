#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "GameObject.h"

class Camera
{
public:
  Camera();
  ~Camera();

  void update();

  void setPrespective(float FOV,float aspectRatio, float near, float far);
  void setOrtho(float left,float right,float bottom, float top, float near,float far);

  mat4& getView()
  {
    return m_View;
  };

  mat4& getProjection()
  {
    return m_Projection;
  };

  vec3& getForward()
  {
    return m_Forward;
  };

  vec3& getRight()
  {
    return m_Right;
  };

  vec3& getUp()
  {
    return m_Up;
  };
private:
  vec3 m_Forward;
  vec3 m_Right;
  vec3 m_Up;

  mat4 m_View;
  mat4 m_Projection;
  GameObject * m_pGameObject;
};

#endif
