#include "createFile.h"

CreateFile::CreateFile(std::string p) : Command(std::move(p)) {}

Result CreateFile::validate() const {
    Result res = validatePath();
    if (!res.success){
        return res;
    }
    std::string name = lastPart(path);
    if (name.empty()){
        return {false, "Error: '/' already exists."};
    }
    if (path.back() == '/'){
        return {false, "Error: the file path must not end with '/'."};
    }
    if (!validateName(name)){
        return {false, "Error: invalid file name."};
    }
    return {true, "OK"};
}

std::unique_ptr<Result> CreateFile::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.createFile(path));
}