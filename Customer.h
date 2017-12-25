#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Customer{
private:
  double timing;
  int items;
  double selectionTime;
public:
  //kept giving me errors for not having this method, should prolly never call though
  Customer (){
    timing = 0;
    items = 0;
    selectionTime = 0;
  }
  //the primary constructor used
  Customer (double t, int i, double st){
    timing = t;
    items = i;
    selectionTime = st;
  }
  //A copy constructor
  Customer (Customer const &newGuy){
    timing = newGuy.timing;
    items = newGuy.items;
    selectionTime = newGuy.selectionTime;
  }
  int getOrderSize (){
    return items;
  }
  double getTimeToGetItem (){
    return selectionTime;
  }
  friend ostream& operator<<(ostream& os, const Customer& me){
    os << me.timing << me.items << me.selectionTime;
    return os;
  }
};
