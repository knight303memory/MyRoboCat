//
// Created by Killua on 2018/2/4.
//

#include "MyRoboCatPCH.h"


std::unique_ptr<RandGen> RandGen::sInstance = nullptr;

RandGen::RandGen() : mFloatDistr(0.f, 1.f) {

}

void RandGen::StaticInit() {
//    sInstance = std::make_unique<RandGen>(); //c++14

    sInstance = std::unique_ptr<RandGen>(new RandGen());

    std::random_device rd;

    sInstance->mGenerator.seed(rd()); // mt
}

void RandGen::Seed(uint32_t inSeed) {
    mGenerator.seed(inSeed);
}

float RandGen::GetRandomFloat() {
    return mFloatDistr(mGenerator);
}

uint32_t RandGen::GetRandomUInt32(uint32_t inMin, uint32_t inMax) {
    std::uniform_int_distribution<uint32_t> dist(inMin, inMax);
    return dist(mGenerator);
}

int32_t RandGen::GetRandomInt32(int32_t inMin, int32_t inMax) {
    std::uniform_int_distribution<int32_t> dist(inMin, inMax);
    return dist(mGenerator);
}

Vector3 RandGen::GetRandomVector(const Vector3 &inMin, const Vector3 &inMax) {
    Vector3 r = Vector3(GetRandomFloat(), GetRandomFloat(), GetRandomFloat());
    return inMin + (inMax - inMin) * r;
}








