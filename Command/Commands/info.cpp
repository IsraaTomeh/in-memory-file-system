#include "info.h"
Info::Info(std::string p) : Command(std::move(p)) {}

Result Info::validate() const { return validatePath(); }

std::unique_ptr<Result> Info::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.info(path));
}