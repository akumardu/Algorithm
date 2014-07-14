#ifndef _SIMPLETIMER_H_
#define _SIMPLETIMER_H_

#define WIN_ENV

#ifdef WIN_ENV
    #include <WTYPES.H>
	typedef long long frequency_t;
#endif

#ifdef MAC_ENV
	#include <inttypes.h>
	typedef uint64_t frequency_t;
#endif

#if defined(UNIX_ENV) 
    #include <sys/time.h>
    #include <sys/resource.h>
	typedef unsigned int frequency_t;
#endif 



class SimpleTimer 
{
public:
    enum unit { MILLI, MICRO };
	SimpleTimer();
	~SimpleTimer();
	void startTimer();
	void stopTimer();
	double getElapsedTime( int displayUnit = MILLI );

private:
	frequency_t startTime, endTime, frequency;
	frequency_t getTimerFrequency();
	frequency_t getTimerTick();    
	double elapsedTime;
	bool isStartTimeSet, isEndTimeSet;
};

#endif
