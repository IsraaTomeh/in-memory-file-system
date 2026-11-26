#include "createDirectory.h"

CreateDirectory::CreateDirectory(std::string p): Command(std::move(p)) {}

Result CreateDirectory::validate() const {
    Result res = validatePath();
    if (!res.success){
        return res;
    }
    std::string name = lastPart(path);
    if (name.empty()){
        return {false, "Error: '/' already exists."};
    }
    if (!validateName(name)){
        return {false, "Error: invalid directory name '" + name + "'."};
    }
    return {true, "OK"};
}

std::unique_ptr<Result> CreateDirectory::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.createDirectory(path));
}
