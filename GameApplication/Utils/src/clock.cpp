#include "clock.h"

const string getLocalTimeStr(){
  time_t currentTime;
  struct tm * timeinfo;
  time(&currentTime);
  timeinfo = localtime ( &currentTime );
  char * asciitime=asctime(timeinfo);
  asciitime[strlen(asciitime)-1]=0;
  return string(asciitime);
}
