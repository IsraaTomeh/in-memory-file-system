#pragma once
#include <string>

struct Result{
    bool success;
    std::string message;

    Result(bool s=false, std::string m="");
   
   
    virtual ~Result()= default;
    virtual std::string toString()const;
};