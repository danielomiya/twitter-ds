//
// Created by Daniel Omiya on 09/05/21.
//

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
/* this file contains a lot of warnings but, as it is external,
 * there's no point in debbuging it
 */
#include "deps/csv.h"
#pragma GCC diagnostic pop

#include "trend.hpp"
#include <string>
#include <vector>

std::vector<Trend> getTrends(const std::string &path);
