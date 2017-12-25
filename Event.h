#pragma once

//#ifndef event_class_h
//#define event_class_h

#include <iostream>
#include <string>
#include <cstdlib>
#include "Customer.h"
using namespace std;

enum EventType {EndShopping, Arrival, EndCheckout};
class Event{
private:
  EventType type;
  double simTime;
  Customer person;
  int index;

public:
  //kept giving me errors for not having this, but should prolly not often call
  Event (){
    simTime = 0;
    index = 0;
    type = Arrival;
  }
  //the main constructor for the Event class
  Event (EventType e, double t, Customer p){
    type = e;
    simTime = t;
    person = p;
  }
  //a copy constructor
  Event (EventType e, double t, Customer c, int i){
    index = i;
    type = e;
    simTime = t;
    person = c;
  }
  double getTime (){
    return simTime;
  }
  EventType getType (){
    return type;
  }
  Customer getCustomer (){
    return person;
  }
  int getOrderSize (){
    return person.getOrderSize();
  }
  int getIndex (){
    return index;
  }
};
