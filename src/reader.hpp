//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef READER_H
#define READER_H

#include "trend.hpp"
#include <string>
#include <vector>

std::vector<Trend> getTrends(const std::string &path);

#endif // READER_H
