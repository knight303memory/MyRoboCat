//
// Created by Killua on 2018/2/10.
//

#ifndef MYROBOCAT_COMMANDLIST_H
#define MYROBOCAT_COMMANDLIST_H


#include <deque>
#include "Command.h"

class CommandList {
public:
    CommandList() {}

    void AddCommand(CommandPtr inCommand);

    void Clear() {
        mCommands.clear();
    }

    int GetCount() const {
        return static_cast<int>(mCommands.size());
    }

    void ProcessCommands(uint32_t inExpectedPlayerId);

    void Write(OutputMemoryBitStream &inOutputStream);

    void Read(InputMemoryBitStream &inInputStream);

private:
    std::deque<CommandPtr> mCommands;

};


#endif //MYROBOCAT_COMMANDLIST_H
