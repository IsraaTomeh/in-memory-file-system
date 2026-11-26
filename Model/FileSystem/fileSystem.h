#pragma once
#include "../File/file.h"
#include <memory>
#include "../Node/node.h"
#include "../../Result/result.h"
#include "../../Result/ReadResult/readResult.h"
#include "../Directory/directory.h"
#include <string>

class FileSystem {

    std::unique_ptr<Directory> root;

public:
   FileSystem();
   Result createFile(const std::string& path);
   Result createDirectory(const std::string& path);
   ReadResult read(const std::string& path, size_t offset, size_t length)const;
   Result write(const std::string& path, size_t offset, const std::string& data);
   Result rename(const std::string& path, const std::string& newName);
   Result remove(const std::string& path);
   Result list(const std::string& path);
   Result info(const std::string& path);
   Result setReadOnly(const std::string& path, bool value);

private:

   Node* resolve(const std::string& path)const;
   static std::vector<std::string> splitPath(const std::string& path);
   static bool validName(const std::string& name);
   static bool validPathSyntax(const std::string& path);
   Result create(const std::string& path, bool isDirectory);
   




};
