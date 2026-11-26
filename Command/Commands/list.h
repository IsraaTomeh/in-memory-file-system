#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class List: public Command {
public:
    explicit List(std::string p);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};
