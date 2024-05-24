#ifndef WORDGENERATOR_H
#define WORDGENERATOR_H

#include <string>
#include <set>
using namespace std;

class WordGenerator
{
private:
  int tileSize;
  std::set<string> startChunks;
  std::set<string> endChunks;
  std::set<string> chunks;
  string tryGenerateWord(int length);
public:
  WordGenerator(int tileSize, string corpusFile);
  string generateWord(int length);
};
#endif