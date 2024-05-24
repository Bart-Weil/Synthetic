// Class for SVG position

#ifndef POSITION_H
#define POSITION_H

#include <iostream>

#include "SVG/SVGElement.h"

using namespace std;

class Position : public SVGElement {
public:
  double x;
  double y;
  Position(double x, double y) {
    this->x = x;
    this->y = y;
  }
  string format() {
    return string("x=") + paramFormat(to_string(x)) + " " + 
      "y=" + paramFormat(to_string(y));
  }
};

#endif
