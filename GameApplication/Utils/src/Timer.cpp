#include "Timer.h"
#include <SDL.h>

Timer::Timer()
{
  m_LastTicks=0;
  m_CurrentTicks=0;
  m_ElapsedTime=0.0f;
  m_TotalTime=0.0f;
}

Timer::~Timer()
{

}

void Timer::start()
{
  m_CurrentTicks=SDL_GetTicks();
	m_TotalTime=0.0f;
}

void Timer::update()
{
    m_LastTicks=m_CurrentTicks;
  	m_CurrentTicks=SDL_GetTicks();
  	m_ElapsedTime = (m_CurrentTicks - m_LastTicks) / 1000.0f;
  	m_TotalTime+=m_ElapsedTime;
    int dt = m_CurrentTicks - m_LastTicks;
    m_FPSSamples.push_back((1.0f / (float)dt)*1000.0f);
    if (m_FPSSamples.size()>100)
    {
      m_FPSSamples.erase(m_FPSSamples.begin());
    }
}

float Timer::getFPS()
{
  float currentFPS=0.0f;
  for (int i=0;i<m_FPSSamples.size();i++)
  {
    currentFPS+=m_FPSSamples[i];
  }
  return currentFPS/m_FPSSamples.size();
}

float Timer::getDeltaTime()
{
  return m_ElapsedTime;
}
