#ifndef SVG_ELEMENT_H
#define SVG_ELEMENT_H
// abstract class for SVG elements

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "SVG/Transform.h"

using namespace std;

class SVGElement {
public:
  string paramFormat(string arg) {
    return "\"" + arg + "\"";
  }

  string formatTransforms(vector<Transform *> transforms) {
    string transformString = "transform=\"";
    for (Transform *transform : transforms) {
      transformString += transform->format() + " ";
    }
    transformString += "\"";
    return transformString;
  }

  virtual string format() = 0;
};

#endif