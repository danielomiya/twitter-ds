//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef TREND_NAME_HPP
#define TREND_NAME_HPP

#include "trend.hpp"

class TrendName : public Trend {
public:
  TrendName() = default;
  TrendName(const Trend &trend) : Trend(trend) {} // NOLINT(google-explicit-constructor)

  bool operator<(const TrendName &rhs) const {
    ++comparisonCounter;
    return name < rhs.name;
  }
  bool operator>(const TrendName &rhs) const {
    ++comparisonCounter;
    return name > rhs.name;
  }
  bool operator<=(const TrendName &rhs) const {
    ++comparisonCounter;
    return name <= rhs.name;
  }
  bool operator>=(const TrendName &rhs) const {
    ++comparisonCounter;
    return name >= rhs.name;
  }
  bool operator==(const TrendName &rhs) const {
    ++comparisonCounter;
    return name == rhs.name;
  }
  bool operator!=(const TrendName &rhs) const {
    ++comparisonCounter;
    return name != rhs.name;
  }
  static int getComparisonCounter() { return comparisonCounter; }
  static int resetComparisonCounter() { return (comparisonCounter = 0); }

private:
  static int comparisonCounter;
};

int TrendName::comparisonCounter = 0;

#endif // TREND_NAME_HPP
