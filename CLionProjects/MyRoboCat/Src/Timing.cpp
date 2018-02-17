//
// Created by Killua on 2018/2/16.
//

#include "MyRoboCatPCH.h"

using namespace std::chrono;
float kDesiredFrameTime = 0.033333333f;

namespace {
    high_resolution_clock::time_point sStartTime;

}

Timing::Timing() {
    sStartTime = high_resolution_clock::now();
}

void Timing::Update() {
    double currentTime = GetTime();
    mDeltaTime = (float) (currentTime - mLastFrameStartTime);

    while (mDeltaTime < kDesiredFrameTime) {
        currentTime = GetTime();
        mDeltaTime = (float) (currentTime - mLastFrameStartTime);
    }

    mDeltaTime = kDesiredFrameTime;
    mLastFrameStartTime = currentTime;
    mFrameStartTimef = static_cast<float >(mLastFrameStartTime);
}

double Timing::GetTime() const {
    auto now = high_resolution_clock::now();
    auto ms = duration_cast<milliseconds>(now - sStartTime).count();
    return static_cast<double>(ms) / 1000;
}
