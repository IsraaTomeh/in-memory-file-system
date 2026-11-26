#include "delete.h"
Delete::Delete(std::string p) : Command(std::move(p)) {}

Result Delete::validate() const { return validatePath(); }

std::unique_ptr<Result> Delete::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.remove(path));
}