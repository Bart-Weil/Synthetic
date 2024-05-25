#include <string>
#include <iostream>

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

Header::Header(int width, int height): width(width), height(height) {}

std::string Header::format() {
  return string("<svg xmlns=\"http://www.w3.org/2000/svg\" width=") +
  paramFormat(to_string(width)) + " " +
  "height=" + 
  paramFormat(to_string(height)) + 
  ">";
}