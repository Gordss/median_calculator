#include <iostream>
#include <fstream>
#include "NumSet.h"

/*
  The algorithm doesn't work with set size greater than 800
  because the vector structure can't relocate enough memory
*/

int main(){
    std::fstream input_file;
    //name of the input file with extension
    std::string fname;
    double input_number;
    std::cout<<"> ";
    std::cin>>fname;
    input_file.open(fname);

    NumSet numbers;

    while(input_file>>input_number){
      input_file.ignore();
      numbers.add_number(input_number);

      if(input_file.fail()){
        break;
      }

    }

    input_file.close();

    numbers.get_median();

    return 0;
}
