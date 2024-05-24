#ifndef ROTATION_H
#define ROTATION_H

#include <iostream>

#include "SVG/Transform.h"

#include "SVG/Transforms/Transforms.h"

using namespace std;

Rotation::Rotation(double angle) {
  this->angle = angle;
}

string Rotation::format() {
  return "rotate(" + to_string(angle) + ")";
}

#endif