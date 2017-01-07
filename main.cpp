#include <iostream>
#include "errors.h"
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"
#include "helper.h"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int main (int argc, char** argv){
  //Check argc
  test_argc(argc);
  //Convert char**argv to a vector<string>
  vector<string> file = get_file(argc, argv);

  //Ceate Plugboard and Reflector objects dynamicallly and configurate them
  Plugboard *pb = new Plugboard(file[0]);
  pb->config_pb();
  Reflector *rf = new Reflector(file[1]);
  rf->config_rf();

  if(argc>4){
    //In the case that Rotor is involved.
    //Creat and configurate Rotors
    int no_of_rotors = (int)file.size()-3;
    int rightmost_rt = no_of_rotors-1;
    vector<int> rt_pos = get_rtpos(file);
    Rotor** rt = creat_rotots(no_of_rotors, file, rt_pos);

    char input;
    /*Read characters in loop and process through Plugboard, Rotors,
    and Reflectors followed by outputing.*/
    while(cin>>ws>>input){
      check_input(input);

      rt[rightmost_rt]->rotate();
      //Plugboard processing (input)
      input=pb->pb_process(input);
      //Rotors forward processing
      for(int i=rightmost_rt; i>=0; i--){
        input=rt[i]->pass_forward(input);
      }
      //Reflector processing
      input=rf->rf_process(input);
      //Rotors backward processing
      for(int i=0; i<=rightmost_rt;i++){
        input=rt[i]->pass_backward(input);
      }
      //Plugboard processing (ouput)
      input=pb->pb_process(input);
      cout<<input;
    }

    delete_rotors(rt, no_of_rotors);
  }else{
    //Process the input in the case of without Rotor.
    char input;
    while(cin>>ws>>input){
      check_input(input);
      input=pb->pb_process(input);
      input=rf->rf_process(input);
      input=pb->pb_process(input);
      cout<<input;
    }
  }

  delete pb;
  delete rf;
  return NO_ERROR;
}
