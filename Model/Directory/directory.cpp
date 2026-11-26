#include "../Directory/directory.h"

Directory::Directory(std::string s) : Node(std::move(s)) {}

bool Directory::hasChild(const std::string& childName)const{
    return find(childName)!=nullptr;
}

bool Directory::isDirectory()const{
    return true;
}

bool Directory::isEmpty()const{
    return children.empty();
}

std::string Directory::getInfo()const {
    return "Type: Directory\nName: " + (parent ? name : "/") + "\nPath: " + getPath()+ "\nItems: " + std::to_string(children.size());
}

std::unique_ptr<Node>Directory::remove(const std::string& childName){
    for(size_t i=0;i<children.size();i++){
        if(children[i]->getName()== childName){
            std::unique_ptr<Node>deleted= std::move(children[i]);
            children.erase(children.begin()+i);
            deleted->setParent(nullptr);
            return deleted;
        }
    }
    return nullptr;

}

Node* Directory::find(const std:: string& childName)const{
    for(const auto& child : children){
        if(child->getName()==childName){
            return child.get();
        }
    }
    return nullptr;
}

bool Directory::add(std::unique_ptr<Node> node){
    if(hasChild(node->getName())){
        return false;
    }
    node->setParent(this);
    children.push_back(std::move(node));
    return true;
}

std::vector<const Node*> Directory::list()const{
    std::vector<const Node*> List;
    for(const auto& child: children){
        List.push_back(child.get());
    }
    return List;
}

size_t Directory::childcnt() const{
    return children.size();
}