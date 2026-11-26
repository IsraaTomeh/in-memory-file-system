#include "setReadOnly.h"
SetReadOnly::SetReadOnly(std::string p, bool v) : Command(std::move(p)), value(v) {}

Result SetReadOnly::validate() const { return validatePath(); }

std::unique_ptr<Result> SetReadOnly::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.setReadOnly(path, value));
}