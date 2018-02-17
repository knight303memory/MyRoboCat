//
// Created by Killua on 2018/2/16.
//

#ifndef MYROBOCAT_TIMING_H
#define MYROBOCAT_TIMING_H


#include <cstdint>

class Timing {
public:
    Timing();

    void Update();

    float GetDeltaTime() const { return mDeltaTime; }

    double GetTime() const;

    float GetTimeF() const {
        return static_cast<float>(GetTime());
    }

    float GetFrameStartTime() const {
        return mFrameStartTimef;
    }

    static Timing sInstance;


private:
    float mDeltaTime;
    uint64_t mDeltaTick;
    double mLastFrameStartTime;
    float mFrameStartTimef;
    double mPerCountDuration;
};


#endif //MYROBOCAT_TIMING_H
