#include "timer.h"
#include "header.h"

LTimer::LTimer()
{
    start_tick_ = 0;
    paused_tick_ = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    mStarted = true;
    mPaused = false;
    start_tick_ = SDL_GetTicks();
}

void LTimer::stop()
{
    mStarted = false;
    mPaused = false;
    start_tick_ = 0;
    paused_tick_ = 0;
}

void LTimer::pause()
{
    if (mStarted && !mPaused){
        mPaused = true;

        paused_tick_ = SDL_GetTicks() - start_tick_;
        start_tick_ = 0;
    }
}

void LTimer::unpaused()
{
    if (mStarted &&  mPaused){
        mPaused = false;
        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0;
    }
}

int LTimer::get_ticks()
{
    int time = 0;
    if (mStarted){
        if (mPaused){
            time = paused_tick_;
        }
        else{
            time = SDL_GetTicks() - start_tick_;
        }
    }
    return time;
}

bool LTimer::is_paused_()
{
    return mPaused && mStarted;
}

bool LTimer::is_started_(){
    return mStarted;
}
