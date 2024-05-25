// Class for SVG position

#ifndef POSITION_H
#define POSITION_H

#include <iostream>

#include "SVG/SVGElement.h"

class Position : public SVGElement {
public:
  double x;
  double y;
  Position(double x, double y) {
    this->x = x;
    this->y = y;
  }
  std::string format() {
    return std::string("x=") + paramFormat(std::to_string(x)) + " " + 
      "y=" + paramFormat(std::to_string(y));
  }
};

#endif
