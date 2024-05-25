#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <iostream>

#include "SVG/Transform.h"

#include "SVG/Transforms/Transforms.h"

Translation::Translation(double x, double y) {
  this->x = x;
  this->y = y;
}

std::string Translation::format() {
  return "translate(" + std::to_string(x) + " " + std::to_string(y) + ")";
}

#endif
