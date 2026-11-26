#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class CreateFile: public Command {
public:
    explicit CreateFile(std::string p);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};