#include "node.h"
#include "../Directory/directory.h"

Node::Node(const std::string n, Directory* p) : name(std::move(n)), parent(p) {}

const std::string& Node::getName()const{
    return name;
}

void Node::setName(const std::string& n){
    name=n;
}

Directory* Node::getParent()const{
    return parent;
}

void Node::setParent(Directory* p){
    
    parent=p;
}

std::string Node::getPath()const{
    if(!parent){
        return "/";
    }
    std::string path= parent->getPath(); 
    if(path!="/"){
        path+= "/";
    }
    return path+name;
}



