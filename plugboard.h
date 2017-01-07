#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include "errors.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class Plugboard{
private:
  string pb_filename; //Plugboard config filename
  vector<int> config; //Vector storing the config data
  map<char, char> pb_mapping; // Mapping from input to output

public:
  Plugboard (string _filename);
  //Check, read and store the configuration pblugboard file
  int read_file();
  //Configuring the plugboard
  void config_pb();
  //Pass a character through plugboard and returns the output
  char pb_process(char input);
  ~Plugboard();
};
#endif
