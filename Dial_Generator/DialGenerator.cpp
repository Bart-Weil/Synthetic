// DialGenerator class writes an svg file (dial.svg) of a
// the dial background, writes (knob.svg) for the knob

#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <cassert>

#include "Acronym_Generator/AcronymGenerator.h"
#include "Word_Generator/WordGenerator.h"

#include "SVG/SVGElement.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

#include "SVG/Transforms/Transforms.h"

#include "Dial_Generator/DialGenerator.h"

void DialGenerator::drawKnob(std::unique_ptr<SVGDiv> &knobDiv) {
  // write knob file, black filled circle with radius size-30, smaller white 
  // white filled circle with radius 2 at top of knob
  std::cout << knobDiv->width << std::endl;
  const int cx = (knobDiv->width)/2;
  const int cy = (knobDiv->height)/2;
  knobDiv->addElement(std::make_unique<Circle>(cx, cy, dialSize-30, "black", 3, "white",  std::vector<std::unique_ptr<Transform>>()));
  knobDiv->addElement(std::make_unique<Circle>(cx, cy - (dialSize-30) + 8, 4, "black", 0, "black",  std::vector<std::unique_ptr<Transform>>()));
}

void DialGenerator::drawBorder(std::unique_ptr<SVGDiv> &bgDiv) {
  const int cx = bgDiv->width/2;
  const int cy = bgDiv->height/2;
  bgDiv->addElement(std::make_unique<Circle>(cx, cy, dialSize-20, "black", 2, "transparent",  std::vector<std::unique_ptr<Transform>>()));
}

void DialGenerator::drawSmallDivs(std::unique_ptr<SVGDiv> &bgDiv, bool isDiscrete, int blankAngle, int smallDivs, int largeDivs) {
  const int cx = bgDiv->width/2;
  const int cy = bgDiv->height/2;
  
  const float incrementLarge = (360-blankAngle) / (largeDivs-1);
  const float initialAngleLarge = (blankAngle/2);

  // write small divisions
  if (!isDiscrete && blankAngle < 270) {
    const float incrementSmall = incrementLarge / (smallDivs+1);
    const float initialAngleSmall = initialAngleLarge + incrementSmall;
    for (int div=0; div<largeDivs-1; ++div) {
      for (int subDiv=0; subDiv<smallDivs; ++subDiv) {
        std::vector<std::unique_ptr<Transform>> transforms;
        transforms.push_back(std::make_unique<Translation>(cx, cy));
        transforms.push_back(std::make_unique<Rotation>(initialAngleSmall + div*incrementLarge + subDiv*incrementSmall));
        transforms.push_back(std::make_unique<Translation>(0, dialSize-20));
        bgDiv->addElement(std::make_unique<Rectangle>(-1, 0, 2, smallDivSize, "black", std::move(transforms)));
      }
    }
  }
}

void DialGenerator::drawLargeDivs(std::unique_ptr<SVGDiv> &bgDiv, bool isDiscrete, int blankAngle, int largeDivs) {
  const int cx = bgDiv->width/2;
  const int cy = bgDiv->height/2;
  
  // write large divisions
  const float incrementLarge = (360-blankAngle) / (largeDivs-1);
  const float initialAngleLarge = (blankAngle/2);
  for (int div=0; div<largeDivs; ++div) {
    std::vector<std::unique_ptr<Transform>> transforms;
    transforms.push_back(std::make_unique<Translation>(cx, cy));
    transforms.push_back(std::make_unique<Rotation>(initialAngleLarge + div*incrementLarge));
    transforms.push_back(std::make_unique<Translation>(0, dialSize-20));
    bgDiv->addElement(std::make_unique<Rectangle>(-1, 0, 2, largeDivSize, "black", std::move(transforms)));
  }
}

void DialGenerator::drawDialLabel(std::unique_ptr<SVGDiv> &bgDiv, std::string name) {
  const int cx = bgDiv->width/2;
  const int cy = bgDiv->height/2;
  // write labels
  bgDiv->addElement(std::make_unique<Text>(cx, cy + dialSize + 10, "Arial", 20, 600, "middle", std::vector<std::unique_ptr<Transform>>(), name));
}

std::string DialGenerator::incToString(int inc, int order, std::string unitString) {
  std::string resultValue, resultSuffix;
  if (abs(order) > 3) {
    int exponent = static_cast<int>(floor(log10(inc > 0 ? inc : 1)));
    std::string orderString = "E" + std::to_string(order + exponent);
    resultValue = std::to_string(inc * pow(10, -exponent));
    resultSuffix = orderString + " " + unitString;

  } else {
    resultValue = std::to_string(inc * pow(10, order));
    resultSuffix = " " + unitString;
  }
  return resultValue.erase(resultValue.find_last_not_of("0")+2, std::string::npos) + resultSuffix;
}

void DialGenerator::drawDivLabels(std::unique_ptr<SVGDiv> &bgDiv, bool isDiscrete, int largeDivs, float initialAngleLarge, float incrementLarge) {
  const int cx = bgDiv->width/2;
  const int cy = bgDiv->height/2;
  
  int acronymLength = distributions->acronymLengthDist(gen);
  std::string unitString = generators->AcronymGen.generateAcronym(acronymLength, false);
  for (int i=0; i<acronymLength; ++i) {
    unitString[i] = distributions->lowercaseDist(gen) ? tolower(unitString[i]) : unitString[i];
  }
  int unitStart = distributions->unitStartDist(gen);
  int unitOrder = distributions->unitOrderDist(gen);

  for (int div=0; div<largeDivs; ++div) {
    std::string anchor;
    float divProgress = static_cast<float>(div)/(largeDivs-1);
    if (divProgress == 0.5) {
      anchor = "middle";
    } else if (divProgress < 0.5) {
      anchor = "end";
    } else {
      anchor = "start";
    }
    std::string word;
    if (isDiscrete) {
      word = generators->WordGen.generateWord(distributions->wordLengthDist(gen));
    } else {
      word = incToString(unitStart+div, unitOrder, unitString);
    }

    std::vector<std::unique_ptr<Transform>> transforms;
    transforms.push_back(std::make_unique<Translation>(cx, cy));
    transforms.push_back(std::make_unique<Rotation>(initialAngleLarge + div*incrementLarge));
    transforms.push_back(std::make_unique<Translation>(0, dialSize-(15-largeDivSize)));
    transforms.push_back(std::make_unique<Rotation>(-(initialAngleLarge+div*incrementLarge)));

    bgDiv->addElement(std::make_unique<Text>(0, 0, "Arial", 12, 600, anchor, std::move(transforms), word));
  }
}

std::pair<std::unique_ptr<SVGElement>, std::unique_ptr<SVGElement>> DialGenerator::generateDial() {
  assert(LargeDivs.min_val >= 2);

  bool isDiscrete = distributions->discreteDist(gen)==1;
  bool labelDivs = distributions->labelDivDist(gen)==1;
  bool labelDial = distributions->labelDialDist(gen)==1;

  int blankAngle = blankAngles[distributions->blankAnglesIndexDist(gen)];
  int largeDivs = distributions->largeDivDist(gen);
  // ensure largeDivs are not too crowded
  if (largeDivs > 4) {
    blankAngle = std::min(blankAngle, 180);
  }
  int smallDivs = distributions->smallDivDist(gen);

  auto knobDiv = std::make_unique<SVGDiv>(1000, 1000, std::move(std::vector<std::unique_ptr<SVGElement>>()));
  auto bgDiv = std::make_unique<SVGDiv>(1000, 1000, std::move(std::vector<std::unique_ptr<SVGElement>>()));

  // write knob file
  drawKnob(knobDiv);

  // write background file, black circle with radius dialSize - 20, transparent fill, black stroke
  drawBorder(bgDiv);
  drawLargeDivs(bgDiv, isDiscrete, blankAngle, largeDivs);
  drawSmallDivs(bgDiv, isDiscrete, blankAngle, smallDivs, largeDivs);

  // place a generated word underneath the dial, first letter capitalised
  if (labelDial) {
    std::string word = generators->WordGen.generateWord(distributions->wordLengthDist(gen));
    word[0] = toupper(word[0]);
    drawDialLabel(bgDiv, word);
  }

  if (labelDivs) {
    drawDivLabels(bgDiv, isDiscrete, largeDivs, blankAngle/2, (360-blankAngle)/(largeDivs-1));
  }

  return std::make_pair(std::move(knobDiv), std::move(bgDiv));
}

DialGenerator::DialGenerator (
  float discreteProb,
  float labelDivProb,
  float labelDialProb,
  int dialSize,
  ParamRange &LargeDivs, 
  ParamRange &SmallDivs
): gen(rd()), LargeDivs(LargeDivs), SmallDivs(SmallDivs),
    discreteProb(discreteProb), labelDivProb(labelDivProb),
    labelDialProb(labelDialProb), dialSize(dialSize) {

  this->distributions = std::make_unique<DialDistributions>();
  distributions->acronymLengthDist = std::uniform_int_distribution<>(minAcronymLength, maxAcronymLength);
  distributions->blankAnglesIndexDist = std::uniform_int_distribution<>(0, numBlankAngles-1);
  distributions->largeDivDist = std::uniform_int_distribution<>(LargeDivs.min_val, LargeDivs.max_val);
  distributions->smallDivDist = std::uniform_int_distribution<>(SmallDivs.min_val, SmallDivs.max_val);
  distributions->wordLengthDist = std::uniform_int_distribution<>(wordMinLength, wordMaxLength);
  distributions->unitStartDist = std::uniform_int_distribution<>(digitMin, digitMax);
  distributions->unitOrderDist = std::uniform_int_distribution<>(unitOrderMin, unitOrderMax);
  distributions->discreteDist = std::bernoulli_distribution(discreteProb);
  distributions->labelDivDist = std::bernoulli_distribution(labelDivProb);
  distributions->labelDialDist = std::bernoulli_distribution(labelDialProb);
  distributions->lowercaseDist = std::bernoulli_distribution(2.0f/(minAcronymLength+maxAcronymLength));
  
  this->generators = std::make_unique<ProcGenerators>(
    WordGenerator(4, "Dial_Generator/corpus.txt"),
    AcronymGenerator()
  );
}

int main() {
  ParamRange LargeDivs(2, 10);
  ParamRange SmallDivs(0, 10);

  DialGenerator dialGenerator(
    0.25,
    0.5,
    1.0,
    100,
    LargeDivs,
    SmallDivs
  );
  auto [knob, dial] = dialGenerator.generateDial();

  std::string bgName = "dial.svg";
  std::string knobName = "knob.svg";
  

  // write the svg files
  std::ofstream bgFile;
  bgFile.open(bgName);
  bgFile << dial->format();
  bgFile.close();

  std::ofstream knobFile;
  knobFile.open(knobName);
  knobFile << knob->format();
  knobFile.close();

  // write the svg files centered on each other, centered in an html file. scaled as to avoid cropping
  std::ofstream htmlFile;
  htmlFile.open("dial.html");
  htmlFile << "<!DOCTYPE html>" << std::endl;
  htmlFile << "<html>" << std::endl;
  htmlFile << "<script src=\"writeDial.js\"></script>"  << std::endl;
  htmlFile << "<body>" << std::endl;
  htmlFile << "<div style=\"position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);\">" << std::endl;
  htmlFile << "<img src=\"" << bgName << "\" style=\"position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);\">" << std::endl;
  htmlFile << "<img src=\"" << knobName << "\" style=\"position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);\">" << std::endl;
  htmlFile << "</div>" << std::endl;
  htmlFile << "</body>" << std::endl;
  htmlFile << "</html>" << std::endl;
  htmlFile.close();

  return 0;
}