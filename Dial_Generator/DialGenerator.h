#ifndef DIALGENERATOR_H
#define DIALGENERATOR_H

#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <cassert>

#include "Word_Generator/WordGenerator.h"
#include "Acronym_Generator/AcronymGenerator.h"

class ParamRange {
public:
  int min_val;
  int max_val;
  ParamRange(int min_val, int max_val);
};

ParamRange::ParamRange(int min_val, int max_val) {
  assert(max_val >= min_val);
  this->min_val = min_val;
  this->max_val = max_val;
}

class DialGenerator
{
private:
  struct DialDistributions {
    // distribution for blank angle at bottom of dial
    std::uniform_int_distribution<> blankAnglesIndexDist;
    // distribution for number of large divisions
    std::uniform_int_distribution<> largeDivDist;
    // distribution for number of small divisions
    std::uniform_int_distribution<> smallDivDist;

    // distribution for word lengths
    std::uniform_int_distribution<> wordLengthDist;
    // distribution for unitString start
    std::uniform_int_distribution<> unitStartDist;
    // distribution for unitString order of magnitude
    std::uniform_int_distribution<> unitOrderDist;

    // distribution for whether the dial is discrete
    std::bernoulli_distribution discreteDist;
    // distribution for whether the dial divisions are labelled
    std::bernoulli_distribution labelDivDist;
    // distribution for whether the dial is labelled
    std::bernoulli_distribution labelDialDist;

    std::uniform_int_distribution<> acronymLengthDist;
    // distribution for whether the acronym letter is lowercase
    std::bernoulli_distribution lowercaseDist;
  };

  struct ProcGenerators {
    WordGenerator WordGen;
    AcronymGenerator AcronymGen;
    ProcGenerators(WordGenerator WordGen, AcronymGenerator AcronymGen): WordGen(WordGen), AcronymGen(AcronymGen) {}
  };

  std::random_device rd;
  std::mt19937 gen;
  
  ParamRange &LargeDivs;
  ParamRange &SmallDivs;

  float discreteProb;
  float labelDivProb;
  float labelDialProb;
  int dialSize;
  
  int smallDivSize = 5;
  int largeDivSize = 10;

  const int borderSpacing = 5;
  static const int numBlankAngles = 3;
  const int blankAngles[numBlankAngles] = {
    60,
    180,
    300
  };

  const int wordMinLength = 4;
  const int wordMaxLength = 8;

  const int digitMin = 0;
  const int digitMax = 9;

  const int unitOrderMin = -6;
  const int unitOrderMax = 6;

  const int minAcronymLength = 1;
  const int maxAcronymLength = 3;

  DialDistributions *distributions;
  ProcGenerators *generators;
  
  void startKnobFile(std::ofstream &knobStream);
  void drawKnob(std::ofstream &knobStream);
  void endKnobFile(std::ofstream &knobStream);

  void startBgFile(std::ofstream &bgStream);
  void drawBorder(std::ofstream &bgStream);
  void drawSmallDivs(std::ofstream &bgStream, bool isDiscrete, int blankAngle, int smallDivs, int largeDivs);
  void drawLargeDivs(std::ofstream &bgStream, bool isDiscrete, int blankAngle, int smallDivs);
  void drawDialLabel(std::ofstream &bgStream, std::string name);
  void drawDivLabels(std::ofstream &bgStream, bool isDiscrete, int largeDivs, float initialAngleLarge, float incrementLarge);
  void endBgFile(std::ofstream &bgStream);

  std::string incToString(int inc, int order, std::string unitString);
public:
  DialGenerator(
    float discreteProb,
    float labelDivProb,
    float labelDialProb,
    int dialSize,
    ParamRange &LargeDivs,
    ParamRange &SmallDivs
  );

  ~DialGenerator() {
    delete distributions;
    delete generators;
  }
  
  void generateDial(std::string bgName, std::string knobName);
};

#endif
