//
// Created by Daniel Omiya on 10/05/21.
//

#include "writer.hpp"
#include <fstream>

void write(const std::string &path, const std::string &content) {
  std::ofstream file(path);
  file.write(content.c_str(), content.size());
  file.close();
}
