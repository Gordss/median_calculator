#pragma once
#include <cassert>
#include <algorithm>
#include <chrono>

double NumSet::select_median(std::vector<double> subset){
    /*check if the subset size is even or odd
      if the size is odd the median will be in the middle
      if the size is even the median is average from the two middle numbers
    */
    if(subset.size()%2 == 1){
        return quickselect(subset, subset.size()/2);
    }else {
        return 0.5 * (quickselect(subset, subset.size()/2 - 1) +
                      quickselect(subset, subset.size()/2));
    }
}

double NumSet::quickselect(std::vector<double> subset, int index){
    //if the subset size is 1 we just return the element
    if(subset.size() == 1){
        assert(index == 0);
        return subset[index];
    }
    //otherwise we choose our pivot
    double pivot = pick_pivot(subset);

    //we split the subset into three
    //the first one is numbers bigger than the pivot
    std::vector<double>high_than_pivot;
    for(double current : subset){
        if(current > pivot) high_than_pivot.push_back(current);
    }

    //the second one is numbers smaller than the pivot
    std::vector<double>low_than_pivot;
    for(double current : subset){
        if(current < pivot) low_than_pivot.push_back(current);
    }

    //and the third is equal the pivot
    size_t equal_pivot = 0;
    for(double current : subset){
        if(current == pivot) equal_pivot++;
    }

    /*
      -if the size of the lower than the pivot numbers is bigger than the index
      then we make quick select on this part

      -if the index is bigger than the size if the lower ones and smaller then
      the size of the bigger ones then we have found out median

      -and in the last case we know that the median is in the bigger than
      the pivot set and we make quick select in this part BUT we change
      the index to be index = index - (low_than_pivot.size() + equal_pivot)
    */
    if(index < low_than_pivot.size()){
        return quickselect(low_than_pivot, index);
    }else if(index < low_than_pivot.size() + equal_pivot){
        //median found
        return pivot;
    }else {
        return quickselect(high_than_pivot,
                           index - low_than_pivot.size() - equal_pivot);
    }
}

double NumSet::pick_pivot(std::vector<double> numbers){
    //check if the set has elements
    assert(numbers.size() > 0);
    //if the size is less than 5 we call the small data pick algorithm
    if(numbers.size() < 5){
        return smalldata_pick(numbers);
    }

    //split into chunks of 5 numbers
    std::vector<std::vector<double> > chunks;
    chunks.resize(1);
    for(double current : numbers){
        if(chunks.back().size() < 5){
            chunks.back().push_back(current);
        }else {
            chunks.resize(chunks.size() + 1);
            chunks.back().push_back(current);
        }
    }

    std::vector<double> medians;

    //here we sort each chunk and then add the median to container with all the medians
    for(std::vector<double> chunk : chunks){
        sort(chunk.begin(), chunk.end());
        if(chunk == chunks.back()){
            if(chunk.size() % 2 == 1){
                medians.push_back(chunk[chunk.size() / 2]);
            }else {
                medians.push_back(0.5 * (chunk[chunk.size() / 2 - 1] + chunk[chunk.size() / 2]));
            }
        }else {
            medians.push_back(chunk[2]);
        }
    }
    //we make quick select on all medians
    double median_of_medians = select_median(medians);
    return  median_of_medians;
}

double NumSet::smalldata_pick(std::vector<double> numbers){
    sort(numbers.begin(), numbers.end());
    if(numbers.size() % 2 == 1){
        return numbers[numbers.size() / 2];
    }else {
        return 0.5 * (numbers[numbers.size() / 2] +
                      numbers[numbers.size() / 2 - 1]);
    }
}

void NumSet::add_number(double new_number){
    this->data.push_back(new_number);
}

double NumSet::get_median(){
    //get the time before the selection
    auto start = std::chrono::high_resolution_clock::now();

    double median = select_median(this->data);

    //get the time after the selection
    auto end = std::chrono::high_resolution_clock::now();

    std::cout<<"Median : "<<median<<'\n';

    std::chrono::duration<double> duration = end - start;
    std::cout<<duration.count()<<" ms\n";

    return median;
}
