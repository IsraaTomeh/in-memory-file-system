#pragma once
#include <memory>
#include "../Command/command.h"
#include "../../Model/FileSystem/fileSystem.h"
#include "../../Result/result.h"
class CommandRunner{
    public:
    std::unique_ptr<Result> run(Command& cmd, FileSystem& fs);
};