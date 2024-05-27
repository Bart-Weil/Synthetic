#include <string>
#include <iostream>

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

SVGDiv::SVGDiv(int width, int height, std::vector<std::unique_ptr<SVGElement>> elements): 
  elements(std::move(elements)) {
    this->width = width;
    this->height = height;
  }

std::string SVGDiv::formatElements() {
  std::string result = "";
  for (auto& element : elements) {
    result += element->format() + "\n";
  }
  return result;
}

std::string SVGDiv::format() {
  return std::string("<svg xmlns=\"http://www.w3.org/2000/svg\" width=") +
  paramFormat(std::to_string(width)) + " " +
  "height=" + 
  paramFormat(std::to_string(height)) + 
  ">\n" +
  formatElements() +
  "</svg>";
}

void SVGDiv::addElement(std::unique_ptr<SVGElement> element) {
  elements.push_back(std::move(element));
}