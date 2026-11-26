#include "rename.h"

Rename::Rename(std::string p, std::string n)
    : Command(p), newName(n) {}

Result Rename::validate() const {
    Result res = validatePath();

    if (!res.success) {
        return res;
    }

    if (!validateName(newName)) {
        return {false, "Error: invalid newName."};
    }

    return {true, "OK"};
}

std::unique_ptr<Result> Rename::execute(FileSystem& fs) {
    Result res = validate();

    if (!res.success) {
        return std::make_unique<Result>(res);
    }

    return std::make_unique<Result>(fs.rename(path, newName));
}