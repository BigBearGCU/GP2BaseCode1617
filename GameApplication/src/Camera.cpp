#include "Camera.h"

Camera::Camera()
{
  m_Forward=vec3(0.0f,0.0f,1.0f);
  m_Right=vec3(1.0f,0.0f,0.0f);
  m_Up=vec3(0.0f,1.0f,0.0f);

  m_View=mat4(1.0f);
  m_Projection=mat4(1.0f);
  m_pGameObject=nullptr;
}

Camera::~Camera()
{

}

void Camera::setPrespective(float FOV,float aspectRatio, float near, float far)
{
  m_Projection = perspective(FOV, aspectRatio, near, far);
}

void Camera::setOrtho(float left,float right,float bottom, float top, float near,float far)
{
  m_Projection=ortho(left,right,bottom,top,near,far);
}

void Camera::update()
{
  //Grab position from the Game Object
  if (m_pGameObject)
    m_View=lookAt(m_pGameObject->getPosition(), m_pGameObject->getPosition()+m_Forward, m_Up);
}
