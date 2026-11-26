#include "commandRunner.h"


std::unique_ptr<Result>CommandRunner::run(Command& cmd, FileSystem& fs){
    Result res=cmd.validate();
    if(!res.success){
        return std::make_unique<Result>(res);
    }
    return cmd.execute(fs);
};