#include "readResult.h"

ReadResult::ReadResult(bool s,std::string m, std::string d, size_t b): 
    Result(s, std::move(m)), data(std::move(d)), bytesRead(b){}

std::string ReadResult::toString()const{
    if(!success){
        return message;
    }
    return data.empty()? "(no data)":data;
}