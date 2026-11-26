#pragma once
#include <string>
#include "../result.h"
struct ReadResult: public Result{
    public:
    std::string data;
    size_t bytesRead;

    ReadResult(bool s=false, std::string m="", std::string d="", size_t b=0);
    std::string toString()const override;

};