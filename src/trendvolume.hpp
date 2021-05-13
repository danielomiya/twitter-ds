//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef TREND_VOLUME_HPP
#define TREND_VOLUME_HPP

#include "trend.hpp"

class TrendVolume : public Trend {
public:
  TrendVolume() = default;
  TrendVolume(const Trend &trend) // NOLINT(google-explicit-constructor)
      : Trend(trend) {}

  bool operator<(const TrendVolume &rhs) const {
    ++comparisonCounter;
    return tweetVolume < rhs.tweetVolume;
  }
  bool operator>(const TrendVolume &rhs) const {
    ++comparisonCounter;
    return tweetVolume > rhs.tweetVolume;
  }
  bool operator<=(const TrendVolume &rhs) const {
    ++comparisonCounter;
    return tweetVolume <= rhs.tweetVolume;
  }
  bool operator>=(const TrendVolume &rhs) const {
    ++comparisonCounter;
    return tweetVolume >= rhs.tweetVolume;
  }
  bool operator==(const TrendVolume &rhs) const {
    ++comparisonCounter;
    return tweetVolume == rhs.tweetVolume;
  }
  bool operator!=(const TrendVolume &rhs) const {
    ++comparisonCounter;
    return tweetVolume != rhs.tweetVolume;
  }
  static int getComparisonCounter() { return comparisonCounter; }
  static int resetComparisonCounter() { return (comparisonCounter = 0); }

private:
  static int comparisonCounter;
};

int TrendVolume::comparisonCounter = 0;

#endif // TREND_VOLUME_HPP
