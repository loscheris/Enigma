#include "reflector.h"
#include "helper.h"
Reflector::Reflector(string _filename): rf_filename(_filename), config(), rf_mapping(){}

int Reflector::read_file(){
  //Incorrect extension of reflector config file
  if(rf_filename.substr(rf_filename.find_last_of(".")+1)!="rf"){
    cerr<<"Incorrect extension of reflector configuration file: "<<rf_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  ifstream in_stream;
  in_stream.open(rf_filename.c_str());
  if(in_stream.fail()){
    cerr<<"Error opening configuration file: "<<rf_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  //Check the validity of the configuration file.
  map<string,int> test;
  string temp;
  while(in_stream>>temp){
    test[temp]++;
    if(((int)test.size()==26 && test[temp]>1) || (int)test.size()>26){
      cerr<<"Incorrect (odd) number of parameters in reflector file "<<rf_filename<<endl;
      in_stream.close();
      exit (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }else if(test[temp]>1){
      cerr<<"Invalid reflector mapping in "<<rf_filename<<endl;
      in_stream.close();
      exit (INVALID_REFLECTOR_MAPPING);
    }else if(!is_numeric(temp)){
      cerr<<"Non-numeric character in reflector file "<<rf_filename<<endl;
      in_stream.close();
      exit (NON_NUMERIC_CHARACTER);
    }else if(!is_in_range(temp)){
      cerr<<"Invalid index in reflector file "<<rf_filename<<endl;
      in_stream.close();
      exit (INVALID_INDEX);
    }
  }

  if(test.size()<26){
    if(test.size()%2 != 0){
      cerr<<"Incorrect (odd) number of parameters in reflector file "<<rf_filename<<endl;
      in_stream.close();
      exit (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }else{
      cerr<<"Insufficient number of mappings in reflector file: "<<rf_filename<<endl;
      in_stream.close();
      exit (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }
  }

  //Storing the numbers in configuration file as vector<int>
  in_stream.clear();
  in_stream.seekg(0);
  int temp_int;
  while(in_stream>>temp_int){
    config.push_back(temp_int);
  }

  in_stream.close();
  return NO_ERROR;
}

void Reflector::config_rf(){
  read_file();
  char temp1;
  char temp2;
  //Configuring mapping between input and output
  for (int i = 0; i <(int)config.size(); i+=2) {
    temp1 = static_cast<char>(config[i]+65);
    temp2 = static_cast<char>(config[i+1]+65);
    rf_mapping[temp1] = temp2;
    rf_mapping[temp2] = temp1;
  }
}


char Reflector::rf_process(char input){
  map<char, char>:: iterator it;
  //Find the input as the key in the map and returns the corresponding value
  it = rf_mapping.find(input);
  return it->second;
}


Reflector::~Reflector(){

};
