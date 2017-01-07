#ifndef ROTOR_H
#define ROTOR_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include <string>
using namespace std;

class Rotor{
private:
  string rt_filename;// configuration file
  Rotor *left;//left rotor
  map<char, char> rt_mapping; // mapping from input to outpout
  vector<int> config;//configuration set
  int difference[26];//A helper array to calculate the mapping after rotation
  int ini_pos; //initial position of the rotor
  int no_rot; //number of rotation
  vector<int> notch; // set of notches

public:
  Rotor(string _filename, int pos);
  //Check, read, and store the rotor configuration file
  int read_file();
  //configuration  wiring
  void config_rt();
  //Function to make one rotation
  void rotate();
  //Conect to the left rotor
  void set_left_rotor(Rotor* &_left);
  //Pass a character from right to left and returns the ouput
  char pass_forward(char input);
  //Pass a character from left to right and returns the output
  char pass_backward(char input);
  ~Rotor();
};
#endif
