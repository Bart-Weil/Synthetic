#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <iostream>

#include "SVG/Transform.h"

#include "SVG/Transforms/Transforms.h"

using namespace std;

Translation::Translation(double x, double y) {
  this->x = x;
  this->y = y;
}

string Translation::format() {
  return "translate(" + to_string(x) + " " + to_string(y) + ")";
}

#endif
