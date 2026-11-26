#pragma once
#include <string>

class Directory;

class Node{

    protected:
    std::string name;
    Directory* parent;

    public:
    explicit Node(const std::string n, Directory* p = nullptr);
    virtual ~Node() = default;
    const std::string& getName()const;
    void setName(const std::string& n);
    Directory* getParent()const;
    void setParent(Directory* p);
    std::string getPath()const;
    virtual bool isDirectory()const=0;
    virtual std::string getInfo()const=0;
    
};
