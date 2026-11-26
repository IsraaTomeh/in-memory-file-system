#pragma once

#include <string>
#include "../Node/node.h"

class File : public Node {
    std::string content;
    bool readOnly;
public:

    File(std::string n);
    size_t size() const;
    bool isReadOnly() const;
    void setReadOnly(bool value);
    std::string read(size_t offset,size_t length) const;
    void write(size_t offset, const std::string& data);
    bool isDirectory() const override;
    std::string getInfo() const override;

};
