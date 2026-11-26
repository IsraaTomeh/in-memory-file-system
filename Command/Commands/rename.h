#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class Rename: public Command {
    std::string newName;

public:
    Rename(std::string p, std::string n);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};