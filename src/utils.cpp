#include "utils.hpp"

std::string replaceSubstring(const std::string &str, const std::string &from,
                             const std::string &to) {
  int start_pos = 0;
  auto copy = str;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    copy.replace(start_pos, from.length(), to);
    start_pos += to.length(); // handles case where 'to' is a substring of 'from'
  }
  return copy;
}
