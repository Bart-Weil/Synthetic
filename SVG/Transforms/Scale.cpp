#ifndef SCALE_H
#define SCALE_H

#include <iostream>

#include "SVG/Transform.h"

#include "SVG/Transforms/Transforms.h"

using namespace std;

Scale::Scale(double x, double y) {
    this->x = x;
    this->y = y;
}
string Scale::format() {
  return "scale(" + to_string(x) + " " + to_string(y) + ")";
}

#endif
