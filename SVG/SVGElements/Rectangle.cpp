// Define a rectangle SVG element.

#include <string>
#include <iostream>

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

Rectangle::Rectangle(double x, double y, double width, double height, std::string fill, std::vector<std::unique_ptr<Transform>> transforms):
    x(x),
    y(y),
    width(width),
    height(height),
    fill(fill),
    transforms(std::move(transforms)) {}

std::string Rectangle::format() {
  return "<rect " + 
  Position(x, y).format() + 
  " width=" + 
  paramFormat(std::to_string(width)) + " " + 
  "height=" + 
  paramFormat(std::to_string(height)) + " " + 
  formatTransforms(transforms) + " " 
  "/>";
}
