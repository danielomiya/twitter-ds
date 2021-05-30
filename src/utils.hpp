//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

template <class T> inline T max(T x, T y) { return (x > y) ? x : y; }

std::string replaceSubstring(const std::string &str, const std::string &from,
                             const std::string &to);

#endif // UTILS_HPP
