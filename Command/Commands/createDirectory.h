#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"

class CreateDirectory : public Command {
public:
    explicit CreateDirectory(std::string p);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};
