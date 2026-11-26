#include "result.h"

Result::Result(bool s, std::string m): success(s), message(std::move(m)){}

std::string Result::toString()const{
    return message;
}