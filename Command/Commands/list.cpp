#include "list.h"
List::List(std::string p) : Command(std::move(p)) {}

Result List::validate() const { return validatePath(); }

std::unique_ptr<Result> List::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.list(path));
}
