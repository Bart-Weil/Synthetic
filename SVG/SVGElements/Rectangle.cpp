// Define a rectangle SVG element.

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

Rectangle::Rectangle(double x, double y, double width, double height, string fill = "black", vector<Transform*> transforms = {}) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->fill = fill;
  this->transforms = transforms;
}
string Rectangle::format() {
  return "<rect " + Position(x, y).format() + " width=" + paramFormat(to_string(width)) + " height=" + paramFormat(to_string(height)) + " " + formatTransforms(transforms) + " />";
}
