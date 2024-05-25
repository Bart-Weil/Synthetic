#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <iostream>

#include "SVG/Transform.h"

class Scale : public Transform {
public:
  double x;
  double y;
  Scale(double x, double y);
  std::string format();
};

class Rotation : public Transform {
public:
  double angle;
  Rotation(double angle);
  std::string format();
};

class Translation : public Transform {
public:
  double x;
  double y;
  Translation(double x, double y);
  std::string format();
};

#endif
