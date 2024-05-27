// Define a rectangle SVG element.

#include <string>
#include <iostream>

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

Circle::Circle(double x, double y, double r, std::string stroke, int strokeWidth, std::string fill, std::vector<std::unique_ptr<Transform>> transforms):
  x(x),
  y(y),
  r(r),
  stroke(stroke),
  strokeWidth(strokeWidth),
  fill(fill),
  transforms(std::move(transforms)) {}

std::string Circle::format() {
  return std::string("<circle") + " " +
    "cx=" + paramFormat(std::to_string(x)) + " " +
    "cy=" + paramFormat(std::to_string(y)) + " " +
    "r=" + paramFormat(std::to_string(r)) + " " +
    "stroke=" + paramFormat(stroke) + " "
    "stroke-width=" + paramFormat(std::to_string(strokeWidth)) + " " +
    "fill=" + paramFormat(fill) + "/>";
}
