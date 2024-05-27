// Define a text SVG element.

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

Text::Text(double x, double y, std::string family, int size, int weight, std::string anchor, std::vector<std::unique_ptr<Transform>> transforms, std::string text):
    x(x),
    y(y),
    family(family),
    size(size),
    weight(weight),
    anchor(anchor),
    transforms(std::move(transforms)),
    text(text) {}
std::string Text::format() {
  return std::string("<text") + " " + 
    Position(x, y).format() + " " +
    "font-family=" + 
    paramFormat(family) + " " +
    "font-size=" + 
    paramFormat(std::to_string(size)) + " " +
    "font-weight=" +
    paramFormat(std::to_string(weight)) + " " +
    "text-anchor=" +
    paramFormat(anchor) + " " +
    formatTransforms(transforms) + 
    ">" +
    text +
    "</text>";
}
