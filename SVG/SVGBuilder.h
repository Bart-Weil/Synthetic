#ifndef WORDGENERATOR_H
#define WORDGENERATOR_H

// Provides an SVGBuilder class that can be used to build SVG files.
// The SVGBuilder holds a list of SVGElements and can write them to a file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "SVG/SVGElement.h"

using namespace std;

class SVGBuilder {
private:
  // Initialize the SVGBuilder with an empty list of SVGElements.
  std::vector<SVGElement *> elements;
public:
  SVGBuilder();
  void addElement(SVGElement *element);
  void writeToFile(std::string filename);
  string writeToString();
};

#endif