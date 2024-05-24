#ifndef DIALGENERATOR_H
#define DIALGENERATOR_H

#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <cassert>

#include "Word_Generator/WordGenerator.h"
#include "Acronym_Generator/AcronymGenerator.h"

using namespace std;

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
    uniform_int_distribution<> blankAnglesIndexDist;
    // distribution for number of large divisions
    uniform_int_distribution<> largeDivDist;
    // distribution for number of small divisions
    uniform_int_distribution<> smallDivDist;

    // distribution for word lengths
    uniform_int_distribution<> wordLengthDist;
    // distribution for unitString start
    uniform_int_distribution<> unitStartDist;
    // distribution for unitString order of magnitude
    uniform_int_distribution<> unitOrderDist;

    // distribution for whether the dial is discrete
    bernoulli_distribution discreteDist;
    // distribution for whether the dial divisions are labelled
    bernoulli_distribution labelDivDist;
    // distribution for whether the dial is labelled
    bernoulli_distribution labelDialDist;

    uniform_int_distribution<> acronymLengthDist;
    // distribution for whether the acronym letter is lowercase
    bernoulli_distribution lowercaseDist;
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
  
  void startKnobFile(ofstream &knobStream);
  void drawKnob(ofstream &knobStream);
  void endKnobFile(ofstream &knobStream);

  void startBgFile(ofstream &bgStream);
  void drawBorder(ofstream &bgStream);
  void drawSmallDivs(ofstream &bgStream, bool isDiscrete, int blankAngle, int smallDivs, int largeDivs);
  void drawLargeDivs(ofstream &bgStream, bool isDiscrete, int blankAngle, int smallDivs);
  void drawDialLabel(ofstream &bgStream, string name);
  void drawDivLabels(ofstream &bgStream, bool isDiscrete, int largeDivs, float initialAngleLarge, float incrementLarge);
  void endBgFile(ofstream &bgStream);

  string incToString(int inc, int order, string unitString);
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
  
  void generateDial(string bgName, string knobName);
};

#endif
