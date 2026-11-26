#pragma once
#include <vector>
#include <memory>
#include <string>

#include "../Node/node.h"

class Directory: public Node {
    std::vector<std::unique_ptr<Node>> children;
public:
    Directory(std::string s);

    bool hasChild(const std::string& childName) const;
    bool isDirectory()const override;
    std::string getInfo()const override;
    std::unique_ptr<Node>remove(const std::string& childName);
    bool isEmpty()const;
    Node* find(const std:: string& childName)const;
    bool add(std::unique_ptr<Node> node);
    std::vector<const Node*> list()const;
    size_t childcnt() const;
};



