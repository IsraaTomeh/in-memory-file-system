#include "write.h"
Write::Write(std::string p, size_t off, std::string d)
    : Command(std::move(p)), offset(off), data(std::move(d)) {}

Result Write::validate()const{ 
    return validatePath(); 
}

std::unique_ptr<Result> Write::execute(FileSystem& fs) {
    return std::make_unique<Result>(fs.write(path, offset, data));
}