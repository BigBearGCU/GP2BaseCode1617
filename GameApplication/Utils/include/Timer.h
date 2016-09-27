#ifndef _TIMER_h
#define _TIMER_h

#include <vector>
#include "NonCopyable.h"

using namespace std;

//This class is used to track time
class Timer:public NonCopyable
{
public:
  Timer();
  ~Timer();

  //Start function, used to start the timer
  void start();
  //update the timer
  void update();

  //get fps
  float getFPS();
  //get delta time
  float getDeltaTime();
private:
  vector<float> m_FPSSamples;
  unsigned int m_LastTicks, m_CurrentTicks;
  float m_ElapsedTime;
  float m_TotalTime;
};

#endif
