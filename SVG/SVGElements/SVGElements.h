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
  std::vector<std::unique_ptr<Transform>> transforms;
public:
  Rectangle(double x, double y, double width, double height, std::string fill, std::vector<std::unique_ptr<Transform>> transforms);
  virtual std::string format() override;
};

class Circle: public SVGElement {
private:
  double x;
  double y;
  double r;
  std::string stroke;
  int strokeWidth;
  std::string fill;
  std::vector<std::unique_ptr<Transform>> transforms;
public:
  Circle(double x, double y, double r, std::string stroke, int strokeWidth, std::string fill,
    std::vector<std::unique_ptr<Transform>> transforms);
  virtual std::string format() override;
};

class Text: public SVGElement {
private:
  double x;
  double y;
  std::string family;
  int size;
  int weight;
  std::string anchor;
  std::vector<std::unique_ptr<Transform>> transforms;
  std::string text;
public:
  Text(double x, double y, std::string family, int size, int weight, std::string anchor, 
  std::vector<std::unique_ptr<Transform>> transforms, std::string text);
  virtual std::string format() override;
};

class SVGDiv: public SVGElement {
private:
  std::vector<std::unique_ptr<SVGElement>> elements;
  std::string formatElements();
public:
  int width;
  int height;
  SVGDiv(int width, int height, std::vector<std::unique_ptr<SVGElement>> elements);
  virtual std::string format() override;
  void addElement(std::unique_ptr<SVGElement> element);
};

#endif
