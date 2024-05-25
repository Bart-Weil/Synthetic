#ifndef WORDGENERATOR_H
#define WORDGENERATOR_H

#include <string>
#include <set>

class WordGenerator
{
private:
  int tileSize;
  std::set<std::string> startChunks;
  std::set<std::string> endChunks;
  std::set<std::string> chunks;
  std::string tryGenerateWord(int length);
public:
  WordGenerator(int tileSize, std::string corpusFile);
  std::string generateWord(int length);
};
#endif