#pragma once
#include "foodstuff.h"

//just a struct comparator
struct Cheapest{
    bool operator()(const Foodstuff& a, const Foodstuff& b){
        return a.getCostPerPound() < b.getCostPerPound();
    }
};