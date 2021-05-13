//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef TREND_HPP
#define TREND_HPP

#include <string>

struct Trend {
  std::string name;
  int tweetVolume;

  friend std::ostream &operator<<(std::ostream &stream, const Trend &trend) {
    stream << trend.name;
    return stream;
  }
};

#endif // TREND_HPP
