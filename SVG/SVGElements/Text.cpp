// Define a text SVG element.

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

Text::Text(double x, double y, std::string family, int size, int weight, std::string anchor = "middle", vector<Transform*> transforms = {}, std::string text) {
  this->x = x;
  this->y = y;
  this->family = family;
  this->size = size;
  this->weight = weight;
  this->anchor = anchor;
  this->transforms = transforms;
  this->text = text;
}
std::string Text::format() {
  return std::string("<text") + " " + 
    Position(x, y).format() + " " +
    "font-family=" + 
    paramFormat(family) + " " +
    "font-size=" + 
    paramFormat(to_string(size)) + " " +
    "font-weight=" +
    paramFormat(to_string(weight)) + " " +
    "text-anchor=" +
    paramFormat(anchor) + " " +
    "transform=" +
    formatTransforms(transforms) + 
    ">" +
    text +
    "</text>";
}
