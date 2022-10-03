//
// Created by 庞博 on 2018-12-19.
//

#pragma once
#ifndef BJFU_TOUR_GUIDE_SCENICSPOT_H
#define BJFU_TOUR_GUIDE_SCENICSPOT_H

#include <ostream>
#include "../Library/String.h"
#include "../Library/Vector.h"
#include "SpotFunction.h"

class ScenicSpot
{
  public:
    ScenicSpot(const Structure::String &name = "", const Structure::String &info = "");

    void functionAnalysis(const Structure::String &info);

    const Structure::String &get_name() const;

    void set_name(const Structure::String &_name);

    const Structure::String &get_info() const;

    void set_info(const Structure::String &_info);

    const Structure::Vector<SpotFunction> &get_function() const;

    friend std::istream &operator>>(std::istream &is, ScenicSpot &scenicSpot);

    friend std::ostream &operator<<(std::ostream &os, const ScenicSpot &scenicSpot);

    bool operator==(const ScenicSpot &rhs) const;

    bool operator!=(const ScenicSpot &rhs) const;

  private:
    Structure::String _name;
    Structure::String _info;
    Structure::Vector<SpotFunction> _function;
};

#endif //BJFU_TOUR_GUIDE_SCENICSPOT_H
