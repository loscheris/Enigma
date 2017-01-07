#ifndef REFLECTOR_H
#define REFLECTOR_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include <string>
using namespace std;

class Reflector{
private:
  string rf_filename; // reflector config filename
  vector<int> config; // vector storing all the congifuration
  map<char,char> rf_mapping; // map from input to output

public:
  Reflector(string _filename);
  //Check, read and store the config file as vector<int>
  int read_file();
  //Mapping the reflector
  void config_rf();
  //Passing a character into reflector and returns the mapped character
  char rf_process(char input);
  ~Reflector();
};
#endif
