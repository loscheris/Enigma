#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include "errors.h"
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

//Function to test whether argc is a valid number
void test_argc(const int& _argc);
//Funtion to check whether the input is upper-case character
void check_input(const char& input);
//Check whether the string contains numbers only
bool is_numeric(const string& test);
//Check whether the string (which contains numbers only) is in between 0 and 25
bool is_in_range(const string& test);
//Return a vector<string> contains all configuration filenames
vector<string> get_file (const int& _argc, char** _argv);
/*Passing all the command line arguements to the function, check the rotor position config
file validility, if valid return all the rotor position stored in vector<int>*/
vector<int> get_rtpos (const vector<string>& file);
//Dynamically creat n Rotors and configurate each of them
Rotor** creat_rotots(const int& no_of_rotors, const vector<string>& file, const vector<int>& rt_pos);
//Delete of the rotors created dynamicallly
void delete_rotors(Rotor**& rt, const int& no_of_rotors);

#endif
