#include "file.h"
#include "string"

File::File(std::string n) : Node(std::move(n)), readOnly(false){}

size_t File::size() const{
    return content.size();
}

bool File::isReadOnly()const{
    return readOnly;
}

void File::setReadOnly(bool value){
    readOnly=value;
}

std::string File::read(size_t offset, size_t length)const{
    return content.substr(offset,length);
}

void File::write(size_t offset, const std::string& data){
    content.replace(offset,data.size(),data);
}

bool File::isDirectory()const{
    return false;
}

std::string File::getInfo() const {
    return "Type:File\nName: "+ name+
     "\nPath: "+ getPath()+
      "\nSize: " + std::to_string(content.size()) +
       " bytes" +"\nRead-only: " + (readOnly ? "yes" : "no");
}







