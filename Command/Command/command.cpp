#include "command.h"

Command::Command(std::string p):path(std::move(p)){}

Result Command::validatePath()const{
    if (path.empty()){
     return {false, "Error: path is empty."};
    }
    if (path[0] != '/'){
        return {false, "Error: path must start with '/'."};
    }
    return {true, "OK"};
}

bool Command::validateName(const std::string& name){
    return !name.empty()&&name!="."&&name!=".."&&name.find('/')==std::string::npos;
}

std::string Command::lastPart(const std::string& p) {
    std::string str = p;
    while (!str.empty() && str.back() == '/'){
        str.pop_back();
    }
    size_t st = str.find_last_of('/');
    return st == std::string::npos ? str : str.substr(st + 1);
}


