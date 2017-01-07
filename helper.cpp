#include "helper.h"

void test_argc(const int& _argc){
  if(_argc==1){
    cerr<<"usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?"<<endl;
    exit (INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }else if(_argc<3){
    cerr<<"Insufficient number of parameters"<<endl;
    exit (INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }
}


void check_input(const char& input){
  if(input<'A'|| input>'Z'){
    cerr<<input<<" is not a valid input character (input characters must be upper case letters A-Z)!"<<endl;
    exit (INVALID_INPUT_CHARACTER);
  }
}


bool is_numeric(const string& test){
  for(int i=0; i<(int)test.length(); i++){
    if(test[i]>'9' || test[i]<'0'){
      return false;
    }
  }
  return true;
}


bool is_in_range(const string& test){
  int temp= atoi(test.c_str());
  if(temp<0||temp>25){
    return false;
  }
  return true;
}


vector<string> get_file (const int& _argc, char** _argv){
  _argv++;
  vector<string> _file;
  for(int i=0; i<_argc-1; i++){
    _file.push_back(*_argv);
    _argv++;
  }

  //In the case of argc=4, check the extension of the last file (program continues only if the last file is .pos).
  if(_argc==4){
    if(_file[2].substr((_file[2].find_last_of(".")+1))=="rot"){
      cerr<<"No configuration file or incorrect extension for staring postions: "<<_file[2]<< endl;
      exit (INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }else if(_file[2].substr((_file[2].find_last_of(".")+1))!="pos"){
      cerr<<"Incorrect extension in file: "<<_file[2]<<endl;
      exit (INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }
  }
  return _file;
}


vector<int> get_rtpos (const vector<string>& file){
  int no_of_rotors = (int)file.size()-3;
  string rtpos_filename = file[file.size()-1];

  //check the extension of the postion config file
  if(rtpos_filename.substr(rtpos_filename.find_last_of(".")+1)!="pos"){
    cerr<<"No configuration file or incorrect extension for staring postions: "<<rtpos_filename<< endl;
    exit (INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }

  ifstream in_stream;
  in_stream.open(rtpos_filename.c_str());
  //Check whether the rotor position file can be opened.
  if(in_stream.fail()){
    cout<<"Error opening configuration file: "<<rtpos_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  string temp;
  //Check whether every string in the rotor postion file is valid
  while(in_stream>>temp){
    if(!is_numeric(temp)){
      cerr<<"Non-numeric character in rotor positions file "<<rtpos_filename<<endl;
      in_stream.close();
      exit (NON_NUMERIC_CHARACTER);
    }else if(!is_in_range(temp)){
      cerr<<"Invalid index in "<<rtpos_filename<<endl;
      in_stream.close();
      exit (INVALID_INDEX);
    }
  }

  in_stream.clear();
  in_stream.seekg(0);
  //placing every numbers in the rotor position file to vector<int>
  vector<int> rt_pos;
  int temp_int;
  while(in_stream>> temp_int){
    rt_pos.push_back(temp_int);
  }
  in_stream.close();

  //Check whether all rotors have starting positions
  int no_rt_pos = (int)rt_pos.size();
  if(no_rt_pos<no_of_rotors){
    cerr<<"No starting position for rotor "<<no_rt_pos<<" in rotor position file: "<<rtpos_filename<<endl;
    exit (NO_ROTOR_STARTING_POSITION);
  }
  return rt_pos;
}


Rotor** creat_rotots(const int& no_of_rotors, const vector<string>& file, const vector<int>& rt_pos){
  //Dynamically creat rotors
  Rotor** rt = new Rotor* [no_of_rotors];
  for(int i=0; i<no_of_rotors; i++){
    rt[i] = new Rotor(file[i+2],rt_pos[i]);
    rt[i]->config_rt();
    if(i>0){
       rt[i]->set_left_rotor(rt[i-1]);
    }
  }
  return rt;
}


void delete_rotors(Rotor**& rt, const int& no_of_rotors){
  for(int i=0; i<no_of_rotors; i++){
    delete rt[i];
  }
  delete[] rt;
}
