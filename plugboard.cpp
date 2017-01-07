#include "plugboard.h"
#include "helper.h"

Plugboard::Plugboard (string _pb_filename) : pb_filename(_pb_filename), config(), pb_mapping(){
}

int Plugboard::read_file(){
  //Incorrect extension of plugboard config file
  if(pb_filename.substr(pb_filename.find_last_of(".")+1)!="pb"){
    cerr<<"Incorrect extension of plugboard configuration file: "<<pb_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  ifstream in_stream;
  in_stream.open(pb_filename.c_str());
  if(in_stream.fail()){
    cerr<<"Error opening configuration file: "<<pb_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  map<string,int> test;
  string temp;
  //Chcking the validity of the configuration file
  while(in_stream>>temp){
    test[temp]++;
    if(((int)test.size()==26 && test[temp]>1) || (int)test.size()>26){
      cerr<<"Incorrect number of parameters in plugboard file "<<pb_filename<<endl;
      in_stream.close();
      exit (INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }else if(test[temp]>1){
      cerr<<"Impossible plugboard configuration in "<<pb_filename<<endl;
      in_stream.close();
      exit (IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }else if(!is_numeric(temp)){
      cerr<<"Non-numeric character in plugboard file "<<pb_filename<<endl;
      in_stream.close();
      exit (NON_NUMERIC_CHARACTER);
    }else if(!is_in_range(temp)){
      cerr<<"Invalid index in plugboard file "<<pb_filename<<endl;
      in_stream.close();
      exit (INVALID_INDEX);
    }
  }

  if(test.size()%2 != 0){
    cerr<<"Incorrect number of parameters in plugboard file "<<pb_filename<<endl;
    in_stream.close();
    exit (INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }
  //Reading data from configuration file and store them into a vector<int>
  in_stream.clear();
  in_stream.seekg(0);
  int temp_int;
  while(in_stream>>temp_int){
    config.push_back(temp_int);
  }
  in_stream.close();

  return NO_ERROR;
}

void Plugboard::config_pb(){
  read_file();
  char temp1;
  char temp2;
  //Connecting innput and output by map
  for (int i = 0; i <(int) config.size(); i+=2) {
    temp1 = static_cast<char>(config[i]+65);
    temp2 = static_cast<char>(config[i+1]+65);
    pb_mapping[temp1] = temp2;
    pb_mapping[temp2] = temp1;
  }
}


char Plugboard::pb_process(char input){
  map<char, char>:: iterator it;
  //Finding the whether a character maps to another one.
  it = pb_mapping.find(input);
  if(it != pb_mapping.end() ){
    return it->second;
  }
  return input;
}

Plugboard::~Plugboard(){
}
