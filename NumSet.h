#pragma once
#include <vector>

class NumSet{
private:
    //number container
    std::vector<double>data;
    //select the index of the median
    double select_median(std::vector<double>);
    //quick select algorithm
    double quickselect(std::vector<double>, int);
    //select pivot function
    double pick_pivot(std::vector<double>);
    //select pivot function for small chunks
    double smalldata_pick(std::vector<double>);
public:
    //add new number to the set
    void add_number(double);
    //get the median of the set
    double get_median();
};

#include "NumSet.cpp"
