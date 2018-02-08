//
// Created by Killua on 2018/2/8.
//

#ifndef MYROBOCAT_SCOREBOARDMANAGER_H
#define MYROBOCAT_SCOREBOARDMANAGER_H


#include <memory>

#include "RoboMath.h"

#include <string>
#include <vector>


class OutputMemoryBitStream;

class InputMemoryBitStream;

class ScoreBoardManager {
public:
    static void StaticInit();

    static std::unique_ptr<ScoreBoardManager> sInstance;

    class Entry {
    public:
        Entry() {}

        Entry(uint32_t inPlayerId, const std::string &inPlayerName, const Vector3 &inColor);

        const Vector3 &GetColor() const {
            return mColor;
        }

        const uint32_t GetPlayerId() const {
            return mPlayerId;
        };

        const std::string &GetPlayerName() const {
            return mPlayerName;
        }

        int GetScore() const {
            return mScore;
        }

        void SetScore(int inScore);

        bool Write(OutputMemoryBitStream &inOutputStream) const;

        bool Read(InputMemoryBitStream &inInputStream);

        static uint32_t GetSerializedSize();

    private:
        Vector3 mColor;
        uint32_t mPlayerId;
        std::string mPlayerName;
        int mScore;
        std::string mFormattedNameScore;
    };

    Entry *GetEntry(uint32_t inPlayerId);

    bool RemoveEntry(uint32_t inPlayerId);

    void AddEntry(uint32_t inPlayerId, const std::string &inPlayerName);

    void IncScore(uint32_t inPlayerId, int inAmount);

    bool Write(OutputMemoryBitStream &inOutputStream) const;

    bool Read(InputMemoryBitStream &inInputStream);


    const std::vector<Entry> &GetEntries() const { return mEntries; }

private:
    ScoreBoardManager();

    std::vector<Entry> mEntries;

    std::vector<Vector3> mDefaultColors;
};


#endif //MYROBOCAT_SCOREBOARDMANAGER_H
