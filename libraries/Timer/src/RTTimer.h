#ifndef RTTIMER_H_
#define RTTIMER_H_

#include <Arduino.h>

class RTTimer
{
  public:
    RTTimer()
    {
        handle = NULL;
    }

    ~RTTimer()
    {
        if (handle)
            free(handle);
    }

    int begin(uint32_t ms, int auto_reload, TimerCallbackFunction_t callback, void *user)
    {
        static int once = 0;
        if (0 == once)
        {
            ms /= 10;
            if (0 == ms)
                ms = 1;
            handle = xTimerCreate("A_TMR", ms, auto_reload, user, callback);
            once = (int)handle;
        }
        return handle != NULL;
    }

    int period(uint32_t ms, uint32_t wait = 0)
    {
        ms /= 10;
        if (0 == ms)
            ms = 1;
        if (handle)
            return xTimerChangePeriod(handle, ms, wait);
        return pdFAIL;
    }

    int reset(uint32_t wait = 0)
    {
        if (handle)
            return xTimerReset(handle, wait);
        return pdFAIL;
    }

    int start(uint32_t wait = 0)
    {
        if (handle)
            return xTimerStart(handle, wait);
        return pdFAIL;
    }

    int stop(uint32_t wait = 0)
    {
        if (handle)
            return xTimerStop(handle, wait);
        return pdFAIL;
    }

  private:
    TimerHandle_t handle;
};

#endif /* RTTIMER_H_ */