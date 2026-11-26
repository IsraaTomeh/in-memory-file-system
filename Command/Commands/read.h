#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class Read: public Command {
    size_t offset;
    size_t length;

public:
    Read(std::string p, size_t offset, size_t length);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};