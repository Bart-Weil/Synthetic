// Provides an SVGBuilder class that can be used to build SVG files.
// The SVGBuilder holds a list of SVGElements and can write them to a file.

#include "SVG/SVGBuilder.h"
#include "SVG/SVGElement.h"

#include <iostream>
#include <fstream>
#include <sstream>

SVGBuilder::SVGBuilder() {
  elements = std::vector<SVGElement *>();
}

// Add an SVGElement to the SVGBuilder.
void SVGBuilder::addElement(SVGElement *element) {
  elements.push_back(element);
}

// Write the SVGElements to a file.
void SVGBuilder::writeToFile(std::string filename) {
  std::ofstream file;
  file.open(filename);

  file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\">" << std::endl;

  for (SVGElement *element : elements) {
    file << element->format() << std::endl;
  }

  file << "</svg>" << std::endl;

  file.close();
}

// Write the SVGElements to a string.
std::string SVGBuilder::writeToString() {
  std::stringstream ss;

  ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\">" << std::endl;

  for (SVGElement *element : elements) {
    ss << element->format() << std::endl;
  }

  ss << "</svg>" << std::endl;

  return ss.str();
}