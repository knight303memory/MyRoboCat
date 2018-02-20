//
// Created by Killua on 2018/2/20.
//

#ifndef MYROBOCAT_WEIGHTEDTIMEMOVINGAVERAGE_H
#define MYROBOCAT_WEIGHTEDTIMEMOVINGAVERAGE_H


#include "Timing.h"

class WeightedTimeMovingAverage {
public:
    WeightedTimeMovingAverage(float inDuration = 5.f) : mDuration(inDuration), mValue(0.f) {
        mTimeLastEntryMade = Timing::sInstance.GetTime();
    }

    void UpdatePerSecond(float inValue) {
        float time = Timing::sInstance.GetTimeF();
        float timeSinceLastEntry = time - mTimeLastEntryMade;
        float valueOverTime = inValue / timeSinceLastEntry;
        float fractionOfDuration = (timeSinceLastEntry / mDuration);
        if (fractionOfDuration > 1.f) {
            fractionOfDuration = 1.f;
        }

        mValue = mValue * (1.f - fractionOfDuration) + valueOverTime * fractionOfDuration;
        mTimeLastEntryMade = time;
    }

    void Update(float inValue) {
        float time = Timing::sInstance.GetTimeF();
        float timeSinceLastEntry = time - mTimeLastEntryMade;

        float fractionOfDuration = (timeSinceLastEntry / mDuration);
        if (fractionOfDuration > 1.f) {
            fractionOfDuration = 1.f;

        }

        mValue = mValue * (1.f - fractionOfDuration) + inValue * fractionOfDuration;
        mTimeLastEntryMade = time;

    }

    float GetValue() const {
        return mValue;
    }

private:
    float mTimeLastEntryMade;
    float mValue;
    float mDuration;
};


#endif //MYROBOCAT_WEIGHTEDTIMEMOVINGAVERAGE_H
