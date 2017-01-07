#include "rotor.h"
#include "helper.h"
Rotor::Rotor(string _filename, int pos):rt_filename(_filename), left(NULL), rt_mapping(), config(), difference(), ini_pos(pos), no_rot(0), notch(){
}


int Rotor::read_file(){
  //Incorrect extension of rotor config file
  if(rt_filename.substr(rt_filename.find_last_of(".")+1)!="rot"){
    cerr<<"Incorrect extension of rotor configuration file: "<<rt_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  ifstream in_stream;
  in_stream.open(rt_filename.c_str());
  if(in_stream.fail()){
    cerr<<"Error opening configuration file: "<<rt_filename<<endl;
    exit (ERROR_OPENING_CONFIGURATION_FILE);
  }

  map<string,int> test;
  map<string, int> test2;
  string temp;
  int count = 0;

  while(in_stream>>temp){
    test[temp]++;
    //Check string validity
    if(test[temp]>1){
      if((int)test.size()<26){
        cerr<<"Invalid mapping of input "<<count<<" to output "<<temp<<" (output "<<temp<<" is already mapped to from input "<<test2.find(temp)->second<<")"<<endl;
        in_stream.close();
        exit (INVALID_ROTOR_MAPPING);
      }else if(test[temp]>2){
        cerr<<"Invalid rotor mapping in "<<rt_filename<<endl;
        in_stream.close();
        exit (INVALID_ROTOR_MAPPING);
      }
    }else if(!is_numeric(temp)){
      cerr<<"Non-numeric character for mapping in rotor file "<<rt_filename<<endl;
      in_stream.close();
      exit (NON_NUMERIC_CHARACTER);
    }else if(!is_in_range(temp)){
      cerr<<"Invalid index in rotor file "<<rt_filename<<endl;
      in_stream.close();
      exit (INVALID_INDEX);
    }
    test2[temp]=count;
    count++;
  }

  if(test.size()<26){
    cerr<<"Not all inputs mapped in rotor file: "<<rt_filename<<endl;
    in_stream.close();
    exit (INVALID_ROTOR_MAPPING);
  }

  //Convert the integers from configuration file to vector<int> config
  in_stream.clear();
  in_stream.seekg(0);
  int temp_int;
  while(in_stream>> temp_int){
    config.push_back(temp_int);
  }
  //Set notch locations
  for(int i=26; i<(int)config.size();i++){
    notch.push_back(config[i]);
  }
  in_stream.close();
  return NO_ERROR;
}


void Rotor::config_rt(){
  read_file();
  char temp1;
  char temp2;
  //Configuring I/O mappings with starting position of 0.
  for(int i=0; i<26; i++){
    temp1 = static_cast<char>(i+65);
    temp2 = static_cast<char>(config[i]+65);
    rt_mapping[temp1] = temp2;
  }
  //Forming the difference array
  for (int i=0; i<26; i++){
    difference[i] = config[i] - i;
  }
  //Set the starting position
  for(int i=0; i<ini_pos; i++){
    rotate();
  }
}


void Rotor::rotate(){
  no_rot++;
  int temp;
  //Shifting the "difference array"
  temp = difference[0];
  for(int i=0; i<25; i++){
    difference[i] = difference [i+1];
  }
  difference[25]=temp;
  //Forming new configuration
  for(int i=0; i<26; i++){
    config[i] = i + difference[i];
    if (config[i]<0) {
      config[i]+=26;
    }else if(config[i]>25){
      config[i]%=26;
    }
  }

  //Form new mapping vector
  char temp1;
  char temp2;
  for(int i=0; i<26; i++){
    temp1 = static_cast<char>(i+65);
    temp2 = static_cast<char>(config[i]+65);
    rt_mapping[temp1] = temp2;
  }

  //In the case of hitting notch
  if(left != NULL){
    for(int i=0; i<(int)notch.size(); i++){
      if(no_rot%26 == notch[i]){
        left->rotate();
      }
    }
  }
}


void Rotor::set_left_rotor(Rotor*& _left){
  left = _left;
}


char Rotor::pass_forward(char input){
  char output;
  //Finging input in the key of the map and output the corresponding value
  output = rt_mapping.find(input)->second;
  return output;
}


char Rotor::pass_backward(char input){
  char output;
  map<char, char>::iterator it;
  //Finding the input in the value of the map and output the corresponding key
  for(it=rt_mapping.begin(); it!= rt_mapping.end(); it++){
    if(it->second == input){
      output = it->first;
    }
  }
  return output;
}


Rotor::~Rotor(){
}
