#ifndef SVG_ELEMENTS_H
#define SVG_ELEMENTS_H

// Define a rectangle SVG element.

#include <vector>
#include <string>
#include <iostream>

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

class Rectangle: public SVGElement {
private:
  double x;
  double y;
  double width;
  double height;
  std::string fill;
  std::vector<Transform*> transforms;
public:
  Rectangle(double x, double y, double width, double height, std::string fill, std::vector<Transform*> transforms);
  std::string format();
};

class Text: public SVGElement {
private:
  double x;
  double y;
  std::string family;
  int size;
  int weight;
  std::string anchor;
  std::vector<Transform*> transforms;
  std::string text;
public:
  Text(double x, double y, std::string family, int size, int weight, std::string anchor, std::vector<Transform*> transforms, std::string text);
  std::string format();
};

class Header: public SVGElement {
private:
  int width;
  int height;
public:
  Header(int width, int height);
  std::string format();
};

#endif
