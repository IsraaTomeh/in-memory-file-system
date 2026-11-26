#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class SetReadOnly: public Command {
    bool value;

public:
    SetReadOnly(std::string p, bool v);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};