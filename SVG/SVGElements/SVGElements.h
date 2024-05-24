#ifndef SVG_ELEMENTS_H
#define SVG_ELEMENTS_H

// Define a rectangle SVG element.

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

class Rectangle : public SVGElement {
private:
  double x;
  double y;
  double width;
  double height;
  string fill;
  vector<Transform*> transforms;
public:
  Rectangle(double x, double y, double width, double height, string fill, vector<Transform*> transforms);
  string format();
};

#endif
