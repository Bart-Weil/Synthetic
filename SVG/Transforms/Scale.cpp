#ifndef SCALE_H
#define SCALE_H

#include <iostream>

#include "SVG/Transform.h"

#include "SVG/Transforms/Transforms.h"


Scale::Scale(double x, double y) {
    this->x = x;
    this->y = y;
}
std::string Scale::format() {
  return "scale(" + std::to_string(x) + " " + std::to_string(y) + ")";
}

#endif
