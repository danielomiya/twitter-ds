//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef TREND_HPP
#define TREND_HPP

#include "utils.hpp"
#include <string>

struct Trend {
  std::string name;
  int tweetVolume;

  friend std::ostream &operator<<(std::ostream &stream, const Trend &trend) {
    auto label = replaceSubstring(trend.name, "\"", "\\\"");
    stream << label;
    return stream;
  }
};

#endif // TREND_HPP
