#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>

int main(){
  srand(time(NULL));
  std::ofstream file;
  file.open("Test_2_DOUBLE.txt");
  for(size_t i=0;i<337;i++){
    file<<(double)rand()/RAND_MAX<<" ";
  }
  return 0;
}
