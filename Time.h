#ifndef __TIME_H__
#define __TIME_H__

void TimeInit();
void TimeNewFrame();
//Returns seconds since last frame
float TimeGetDeltaTime();
float TimeGetTimeSeconds();

#endif
