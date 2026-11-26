#include "console.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include "../Command/Commands/createDirectory.h"
#include "../Command/Commands/createFile.h"
#include "../Command/Commands/delete.h"
#include "../Command/Commands/info.h"
#include "../Command/Commands/list.h"
#include "../Command/Commands/read.h"
#include "../Command/Commands/rename.h"
#include "../Command/Commands/setReadOnly.h"
#include "../Command/Commands/write.h"

std::string Console::prompt(const std::string& label) {
    std::cout << label;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

bool Console::promptNumber(const std::string& label, size_t& val) {
    std::string s = prompt(label);
    bool isDigit = std::all_of(s.begin(), s.end(), [](unsigned char c) { return std::isdigit(c); });
    if (s.empty() || s.size() > 9 || !isDigit) {
        std::cout << "[Fail] Error: enter a number (0-9).\n";
        return false;
    }
    val = std::stoul(s);
    return true;
}

void Console::showMenu() const {
    std::cout << "\n------In-Memory File System ------\n"
                 "1. Create file\n"
                 "2. Create directory\n"
                 "3. Read file\n"
                 "4. Write file\n"
                 "5. Rename\n"
                 "6. Delete\n"
                 "7. List directory\n"
                 "8. Info\n"
                 "9. Set/clear read-only\n"
                 "0. Exit\n> ";
}

std::unique_ptr<Command> Console::readCommand(const std::string& choice) {
    if (choice == "1"){
        return std::make_unique<CreateFile>(prompt("File path: "));
    }
    if (choice == "2") {
        return std::make_unique<CreateDirectory>(prompt("Directory path: "));
    }
    if (choice == "3") {
        std::string path = prompt("File path: ");
        size_t offset, length;
        if (!promptNumber("Offset: ", offset) || !promptNumber("Length: ", length)){
            return nullptr;
        }
        return std::make_unique<Read>(path, offset, length);
    }
    if (choice == "4") {
        std::string path = prompt("File path: ");
        size_t offset;
        if (!promptNumber("Offset: ", offset)) return nullptr;
        std::string data = prompt("Data: ");
        return std::make_unique<Write>(path, offset, data);
    }
    if (choice == "5") {
        std::string path = prompt("Path: ");
        std::string newName = prompt("New name: ");
        return std::make_unique<Rename>(path, newName);
    }
    if (choice == "6"){
        return std::make_unique<Delete>(prompt("Path: "));
    }
    if (choice == "7") {
        return std::make_unique<List>(prompt("Directory path: "));
    }
    if (choice == "8") {
        return std::make_unique<Info>(prompt("Path: "));
    }
    if (choice == "9") {
        std::string path = prompt("File path: ");
        std::string val = prompt("Read-only? (y/n): ");
        if (val != "y" && val != "n") {
            std::cout << "[Fail] Error: enter y or n.\n";
            return nullptr;
        }
        return std::make_unique<SetReadOnly>(path, val == "y" ? true : false);
    }
    std::cout << "[Fail] Error: invalid choice.\n";
    return nullptr;
}

void Console::printResult(const Result& r) const {
    std::cout << (r.success ? "[Success] " : "[Fail] ") << r.toString() << "\n";
}

void Console::run() {
    showMenu();
    while (true) {
        std::string choice;
        if (!std::getline(std::cin, choice) || choice == "0"){
            break;
        }

        std::unique_ptr<Command> cmd= readCommand(choice);
        if (cmd){
            printResult(*runner.run(*cmd, fs));
        }
    }
    std::cout << "Exiting...\n";
}