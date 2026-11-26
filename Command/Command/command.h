#pragma once
#include <memory>
#include <string>
#include "../../Model/FileSystem/fileSystem.h"
#include "../../Result/result.h"
class Command{
    protected:
    std::string path;
    explicit Command(std::string p);

    Result validatePath()const;
    static bool validateName(const std::string& name);
    static std::string lastPart(const std::string& path);

    public:
    virtual Result validate()const=0;
    virtual std::unique_ptr<Result> execute(FileSystem& fs)=0;
    virtual ~Command()=default;

};