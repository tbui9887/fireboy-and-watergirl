
#ifndef TIMER_H_
#define TIMER_H_
#include "header.h"

class LTimer
{
public:
    LTimer();

    void start();
    void stop();
    void pause();
    void unpaused();

    int get_ticks();

    bool is_paused_();
    bool is_started_();
private:
    int start_tick_;
    int paused_tick_;
    bool mPaused;
    bool mStarted;

};

string set_standard_time (int ms);

#endif // TIMER_H_
