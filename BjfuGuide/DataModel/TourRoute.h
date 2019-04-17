//
// Created by 庞博 on 2018-12-19.
//

#pragma once
#ifndef BJFU_TOUR_GUIDE_TOURROUTE_H
#define BJFU_TOUR_GUIDE_TOURROUTE_H

#include <ostream>

class TourRoute
{
  public:
    explicit TourRoute(int _routeLength = 0);

    int get_routeLength() const;

    void set_routeLength(int _routeLength);

    friend std::istream &operator>>(std::istream &is, TourRoute &route);

    friend std::ostream &operator<<(std::ostream &os, const TourRoute &route);

    bool operator<(const TourRoute &rhs) const;

    bool operator>(const TourRoute &rhs) const;

    bool operator<=(const TourRoute &rhs) const;

    bool operator>=(const TourRoute &rhs) const;

    bool operator==(const TourRoute &rhs) const;

    bool operator!=(const TourRoute &rhs) const;

  private:
    int _routeLength;
};


#endif //BJFU_TOUR_GUIDE_TOURROUTE_H
