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
#include "SVG/SVGBuilder.h"
#include "SVG/Position.h"

#include "SVG/SVGElements/SVGElements.h"

#include "SVG/Transforms/Transforms.h"

#include "Dial_Generator/DialGenerator.h"

void DialGenerator::startKnobFile(std::ofstream &knobStream) {
  knobStream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">" << std::endl;
}

void DialGenerator::drawKnob(std::ofstream &knobStream) {
  // write knob file, black filled circle with radius size-30, smaller white 
  // white filled circle with radius 2 at top of knob
  knobStream << "<circle cx=\"500\" cy=\"500\" r=\"" << dialSize-30 << "\" stroke=\"black\" stroke-width=\"3\" fill=\"white\" />" << std::endl;
  knobStream << "<circle cx=\"500\" cy=\"" << (500 - (dialSize-30) + 8) << "\" r=\"4\" stroke=\"black\" stroke-width=\"0\" fill=\"black\" />" << std::endl;
}

void DialGenerator::endKnobFile(std::ofstream &knobStream) {
  knobStream << "</svg>" << std::endl;
}

void DialGenerator::startBgFile(std::ofstream &bgStream) {
  bgStream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">" << std::endl;
}

void DialGenerator::drawBorder(std::ofstream &bgStream) {
  bgStream << "<circle cx=\"500\" cy=\"500\" r=\"" << dialSize - 20 << "\" stroke=\"black\" stroke-width=\"2\" fill=\"transparent\" />" << std::endl;
}

void DialGenerator::drawSmallDivs(std::ofstream &bgStream, bool isDiscrete, int blankAngle, int smallDivs, int largeDivs) {
  const float incrementLarge = (360-blankAngle) / (largeDivs-1);
  const float initialAngleLarge = (blankAngle/2);

  // write small divisions
  if (!isDiscrete && blankAngle < 270) {
    const float incrementSmall = incrementLarge / (smallDivs+1);
    const float initialAngleSmall = initialAngleLarge + incrementSmall;
    for (int div=0; div<largeDivs-1; ++div) {
      for (int subDiv=0; subDiv<smallDivs; ++subDiv) {
        std::vector<Transform*> transforms;
        transforms.push_back(new Translation(500, 500));
        transforms.push_back(new Rotation(initialAngleSmall + div*incrementLarge + subDiv*incrementSmall));
        transforms.push_back(new Translation(0, dialSize-20));
        bgStream << Rectangle(-1, 0, 2, smallDivSize, "black", transforms).format() << std::endl;
        // bgStream << "<rect x=\"-1\" y=\"0\" width=\"2\" height=\"" << smallDivSize << "\" fill=\"black\" transform=\"translate(500 500) " <<
        // "rotate(" << initialAngleSmall + div*incrementLarge + subDiv*incrementSmall << ")" << " translate(0 " << dialSize-20 << ")\"/>" << std::endl;
      }
    }
  }
}

void DialGenerator::drawLargeDivs(std::ofstream &bgStream, bool isDiscrete, int blankAngle, int largeDivs) {
  // write large divisions
  const float incrementLarge = (360-blankAngle) / (largeDivs-1);
  const float initialAngleLarge = (blankAngle/2);
  for (int div=0; div<largeDivs; ++div) {
    std::vector<Transform*> transforms;
    transforms.push_back(new Translation(500, 500));
    transforms.push_back(new Rotation(initialAngleLarge + div*incrementLarge));
    transforms.push_back(new Translation(0, dialSize-20));
    bgStream << Rectangle(-1, 0, 2, largeDivSize, "black", transforms).format() << std::endl;
    // bgStream << "<rect x=\"-1\" y=\"0\" width=\"2\" height=\"" << largeDivSize << "\" fill=\"black\" transform=\"translate(500 500) " <<
    // "rotate(" << initialAngleLarge + div*incrementLarge << ")" << " translate(0 " << dialSize-20 << ")\"/>" << std::endl;
  }
}

void DialGenerator::drawDialLabel(std::ofstream &bgStream, std::string name) {
  // write labels
  bgStream << "<text x=\"500\" y=\"" << 500 + dialSize + 10 << "\" font-family=\"Arial\" font-size=\"20\" font-weight=\"600\" text-anchor=\"middle\">" << name << "</text>" << std::endl;
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

void DialGenerator::drawDivLabels(std::ofstream &bgStream, bool isDiscrete, int largeDivs, float initialAngleLarge, float incrementLarge) {
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

    bgStream << "<text x=\"0\" y=\"0\" font-family=\"Arial\" font-size=\"12\" font-weight=\"600\" "
    << "text-anchor=\"" << anchor << "\" transform=\"translate(500, 500) "
    << "rotate(" << initialAngleLarge + div*incrementLarge << ") translate(0 " << dialSize-(15-largeDivSize) << " )"
    << "rotate(" << -(initialAngleLarge + div*incrementLarge) << ")\">"
    << word << "</text>" << std::endl;
  }
}

void DialGenerator::endBgFile(std::ofstream &bgStream) {
  bgStream << "</svg>" << std::endl;
}

void DialGenerator::generateDial(std::string bgName, std::string knobName) {
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

  // open streams for writing bg and knob files
  std::ofstream knobStream;
  knobStream.open(knobName);
  std::ofstream bgStream;
  bgStream.open(bgName);

  // write knob file
  startKnobFile(knobStream);
  drawKnob(knobStream);
  endKnobFile(knobStream);

  // write background file, black circle with radius dialSize - 20, transparent fill, black stroke
  startBgFile(bgStream);
  drawBorder(bgStream);
  drawLargeDivs(bgStream, isDiscrete, blankAngle, largeDivs);
  drawSmallDivs(bgStream, isDiscrete, blankAngle, smallDivs, largeDivs);

  // place a generated word underneath the dial, first letter capitalised
  if (labelDial) {
    std::string word = generators->WordGen.generateWord(distributions->wordLengthDist(gen));
    word[0] = toupper(word[0]);
    drawDialLabel(bgStream, word);
  }

  if (labelDivs) {
    drawDivLabels(bgStream, isDiscrete, largeDivs, blankAngle/2, (360-blankAngle)/(largeDivs-1));
  }

  endBgFile(bgStream);

  bgStream.close();

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

  DialDistributions *distributions = new DialDistributions();
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
  this->distributions = distributions;
  
  this->generators = new ProcGenerators(
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
  dialGenerator.generateDial("bg.svg", "knob.svg");

  return 0;
}