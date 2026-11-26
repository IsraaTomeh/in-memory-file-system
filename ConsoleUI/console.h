#pragma once
#include <memory>
#include <string>
#include "../Command/CommandRunner/commandRunner.h"
#include "../Command/Command/command.h"
#include "../Model/FileSystem/fileSystem.h"
#include "../Result/result.h"

class Console {
    FileSystem fs;
    CommandRunner runner;
    std::string prompt(const std::string& label);             
    bool promptNumber(const std::string& label, size_t& out);  
    void showMenu() const;
    std::unique_ptr<Command> readCommand(const std::string& choice);  
    void printResult(const Result& r) const;
public:
    void run();
};