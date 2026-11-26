#include "fileSystem.h"

FileSystem::FileSystem() : root(std::make_unique<Directory>("/")) {}

Result FileSystem::createFile(const std::string& path) {
    return create(path,false);
}

Result FileSystem::createDirectory(const std::string& path) {
    return create(path,true);
}

ReadResult FileSystem::read(const std::string& path, size_t offset, size_t length)const{
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    if(node->isDirectory()){
        return {false,"Error: can not read a directory."};
    }
    File* file=static_cast<File*>(node);
    if(offset>file->size()){
        return {false, "Error: offset exceeded file size."};
    }
    std::string data=file->read(offset,length);
    return {true,"read successfuly.",std::move(data),data.size()};
}

Result FileSystem::write(const std::string& path, size_t offset, const std::string& data){
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    if(node->isDirectory()){
        return {false,"Error: can not write on a directory."};
    }
    File* file=static_cast<File*>(node);
    if(offset>file->size()){
        return {false, "Error: offset exceeded file size."};
    }
    if(file->isReadOnly()){
        return {false,"Error: file is read_only."};
    }
    file->write(offset,data);
    return {true,"written succesfuly."};
    
}

Result FileSystem::rename(const std::string& path, const std::string& newName){
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    if(root.get()==node){
        return {false,"Error: root can't renamed."};
    }
    if(!node->isDirectory()&&static_cast<File*>(node)->isReadOnly()){
        return {false,"Error: file is read_only."};
    }
    if(!validName(newName)){
        return {false,"Error: Invalid Name"};
    }
    if(node->getParent()->hasChild(newName)){
        return {false,"Error: "+newName+ " already exist."};
    }
    node->setName(newName);
    return {true,"renamed succesfuly."};
}


Result FileSystem::remove(const std::string& path){
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    if(root.get()==node){
        return {false,"Error: root can't removed."};
    }

    if(!node->isDirectory()){
        if(static_cast<File*>(node)->isReadOnly()){
            return {false,"Error: file is read_only."};
        }
        node->getParent()->remove(node->getName());
        return {true,"file deleted succesfully."};
    }
    else {
        if(static_cast<Directory*>(node)->isEmpty()){
            node->getParent()->remove(node->getName());
            return {true,"directory deleted succesfully."};
        }
        return {false,"Error: directory is not empty."};
    }
    
}

Result FileSystem::list(const std::string& path){
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    if(!node->isDirectory()){
        return {false,"Error: not a directory."};
    }
    auto List=static_cast<Directory*>(node)->list();
    std::string res="";
    for(auto* it:List){
        if(it->isDirectory()){
            res+="[d] ";
            res+=it->getName();
        }
        else{
            res+="[f] ";
            res+=it->getName();
        }
    }
    return {true,res};
}

Result FileSystem::info(const std::string& path){
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    return {true,node->getInfo()};
}

Result FileSystem::setReadOnly(const std::string& path, bool value){
    Node* node= resolve(path);
    if(!node){
        return {false,"Error: no path found."};
    }
    if(node->isDirectory()){
        return {false, "Error: can't set read_only to a directory."};
    }
    File* file=static_cast<File*>(node);
    file->setReadOnly(value);
    return {true,"set succesfully."};
}


Node* FileSystem::resolve(const std::string& path)const{
    if(!validPathSyntax(path)){
        return nullptr;
    }
    Node* node= root.get();
    for(const auto& n: splitPath(path)){
        if(!(node->isDirectory())){
            return nullptr;
        }
        node= static_cast<Directory*>(node)->find(n);
        if(!node){
            return nullptr;
        }
    }
    return node;
}

bool FileSystem::validName(const std::string& name){
    return !name.empty()&& name!="." && name!=".." && name.find('/')==std::string::npos;
}

bool FileSystem::validPathSyntax(const std::string& name){
    return !name.empty()&&name[0]=='/';
}

std::vector<std::string> FileSystem::splitPath(const std::string& path){
    std::vector<std::string> Path;
    std::string node;
    for(auto c: path){
        if(c=='/'){
            if(!node.empty()){
                Path.push_back(node);
                node.clear();
            }
        }
        else{
            node+=c;
        }
    }
    if(!node.empty()){
        Path.push_back(node);
    }
    return Path;
}

Result FileSystem::create(const std::string& path, bool isDirectory){
    if(!validPathSyntax(path)){
        return {false,"Error: phath must start with '/'."};
    }
    auto Path=splitPath(path);
    if(Path.empty()){
        return {false, "Error: '/' is alredy exist."};
    }

    std::string newName=Path.back();
    if(!validName(newName)){
        return {false, "Error: Invalid name" + newName +"."};
    }
    Path.pop_back();
    Node* curr=root.get();
    for(const auto& p:Path){
        if(!curr->isDirectory()){
            return {false, "Error: " +curr->getName()+ " is not a directory."};
        }
        curr= static_cast<Directory*>(curr)->find(p);
        if(!curr){
            return {false, "Error: perant not found."};
        }
        if(!curr->isDirectory()){
            return {false, "Error: perant is not a directory"};
        }
    }
        Directory* d=static_cast<Directory*>(curr);
        if(d->hasChild(newName)){
            return {false, "Error: "+ newName+ " is alredy exist"};
        }
        std::unique_ptr<Node> newNode;
        if(isDirectory){
            newNode=std::make_unique<Directory>(newName);
        }
        else{
            newNode=std::make_unique<File>(newName);
        }
        d->add(std::move(newNode));
        return {true, isDirectory? newName +" directory created successfuly":newName+" File created successfuly"};
    


}