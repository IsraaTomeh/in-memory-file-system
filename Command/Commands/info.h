#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class Info: public Command {
public:
    explicit Info(std::string p);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};