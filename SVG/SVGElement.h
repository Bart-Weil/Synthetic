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

class SVGElement {
public:
  std::string paramFormat(std::string arg) {
    return "\"" + arg + "\"";
  }

  std::string formatTransforms(std::vector<Transform *> transforms) {
    std::string transformString = "transform=\"";
    for (Transform *transform : transforms) {
      transformString += transform->format() + " ";
    }
    transformString += "\"";
    return transformString;
  }

  virtual std::string format() = 0;
};

#endif