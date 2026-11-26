#include "read.h"
Read::Read(std::string p, size_t offset, size_t length)
    : Command(std::move(p)), offset(offset), length(length) {}

Result Read::validate() const{
    return validatePath(); 
}

std::unique_ptr<Result> Read::execute(FileSystem& fs) {
    return std::make_unique<ReadResult>(fs.read(path, offset, length));
}