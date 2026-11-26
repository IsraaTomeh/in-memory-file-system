#pragma once
#include <memory>
#include <string>
#include "../Command/command.h"
class Write: public Command {
    size_t offset;
    std::string data;

public:
    Write(std::string p, size_t off, std::string d);
    Result validate() const override;
    std::unique_ptr<Result> execute(FileSystem& fs) override;
};