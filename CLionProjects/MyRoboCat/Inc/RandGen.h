//
// Created by Killua on 2018/2/4.
//

#ifndef MYROBOCAT_RANDGEN_H
#define MYROBOCAT_RANDGEN_H


#include <memory>
#include <random>
#include "RoboMath.h"

class RandGen {
public:
    static std::unique_ptr<RandGen> sInstance;

    RandGen();

    static void StaticInit();

    void Seed(uint32_t inSeed);

    std::mt19937 &GetGeneratorRef() { return mGenerator; }

    float GetRandomFloat();

    uint32_t GetRandomUInt32(uint32_t inMin, uint32_t inMax);

    int32_t GetRandomInt32(int32_t inMin, int32_t inMax);

    Vector3 GetRandomVector(const Vector3 &inMin, const Vector3 &inMax);

private:
    std::mt19937 mGenerator;
    std::uniform_real_distribution<float> mFloatDistr;
};


#endif //MYROBOCAT_RANDGEN_H
