// basic file operations
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Customer.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "RegisterQueue.h"
#include "PriorityLinked.h"
using namespace std;

class StoreSimulator{

private:
  PriorityLinked events;
  vector<RegisterQueue<Event> > registers;
  double simClock;
  double lastEvent;
public:
  StoreSimulator(){
    simClock = 0;
    lastEvent = 0;
    registers = vector<RegisterQueue<Event> > ();
    events = PriorityLinked ();
  }
  void startSimulation() {
    loadRegisters( 6, 4);
    loadCustomerData();

    while((events.getSize()) > 0){
      Event e = events.pop();
      simClock = e.getTime();
      if(e.getType() == Arrival){
        handleArrival(e);
        cout << "Arrival: " << fixed << simClock << endl;
      }else if(e.getType() == EndShopping){
        handleEndShopping(e);
        cout << "EndShopping: " << fixed << simClock << endl;
      }else{
        handleEndCheckout(e);
        registers.at(e.getIndex()).CUp();
        cout << "endCheckout: " << fixed << simClock << endl;
      }
    }
    for (int i = 0; i < registers.size(); i++){
      if (registers.at(i).isAuto()){
        cout << "AutoRegister: ";
      } else {
        cout << "NormalRegister: ";
      }
      cout << "total waitime: " << registers.at(i).getWait() << " ";
      cout << "total customers: " << registers.at(i).CCount() << " ";
      cout << "average wait: " << registers.at(i).getWait()/registers.at(i).CCount() << endl;
    }
    cout << "total average wait per user: " << fixed << totalAverage() << endl;
  }

  void loadCustomerData(){

    double simTime, avgSelectionTime;
    int items;
    ifstream myfile ("/Users/matthew/Downloads/Starter Code/ShopSim/arrival.txt");
    if (myfile.is_open()){
      while ( myfile >> simTime >> items >> avgSelectionTime){
        Customer cust(simTime, items, avgSelectionTime) ;
        cout << cust << endl;
        Event e(Arrival, simTime, cust);
        events.enqueue(e);
        cout << e.getCustomer();
      }
      myfile.close();
    }else{
    throw(1);
    }
  }

  void loadRegisters(int numNormal, int numSelfScan){
    for(int i = 0; i < numNormal; i ++){
      RegisterQueue<Event> r(1.5, .01);
      registers.push_back(r);
    }
    for(int i = 0; i < numSelfScan; i++){
      RegisterQueue<Event> r(3.0, .04);
      registers.push_back(r);
    }
  }
  //handleArrival creates a endShopping event and puts it into the events queue
  //requires: e has a valid customer
  //returns: nothing, but there is a new node in the events queue
  void handleArrival(Event& e){
    incrementWait();
    Customer c = e.getCustomer();
    double finishShopping = simClock + (simClock + c.getOrderSize() * c.getTimeToGetItem());
    Event next(EndShopping, finishShopping, c);
    events.enqueue(next);
  }
  //handleEndShopping either puts the customer into the registerqueue or puts them into events if
  //the the register is empty and not running
  //requires: registers is not empty
  //returns: nothing, but puts either a new customer into a registers line or puts them into the events queue as an EndCheckout
  void handleEndShopping(Event& e){
    incrementWait ();
    int shortestLine = registers.at(0).getSize();
    int index = 0;
    for (int i = 1; i < registers.size(); i++){
      if (registers.at(i).getSize() < shortestLine){
        shortestLine = registers.at(i).getSize();
        index = i;
        cout << index << endl;
      }
    }
    //= registers.at(index).customers + 1;
    if ((shortestLine) == 0 && !(registers.at(index).inUse())){
      double finishCheckout = (e.getOrderSize() * registers.at(index).timePerItem + registers.at(index).timeToPay + simClock);
      Event next (EndCheckout, finishCheckout, e.getCustomer(), index);
      events.enqueue(next);
      registers.at(index).Using();
    }else{
      registers.at(index).enqueue(e);
    }
  }
  //processes the customer leaving mostly by seeing if there is another waiting and them puts them into the events as a EndCheckout
  //event or if there is no one it marks the register as not in use
  //requires: registers is not empty, the event dequeued needs to have an index
  //returns: nothing, but the customer will be out of the register and it will either be marked open or it will have a new customer in it
  void handleEndCheckout(Event e){
    incrementWait();
    if (registers.at(e.getIndex()).getSize() == 0){
      registers.at(e.getIndex()).stop();
    } else {
      Event eve = registers.at(e.getIndex()).dequeue();
      cout << eve.getCustomer() << endl;
      double finishCheckout = (e.getOrderSize() * registers.at(e.getIndex()).timePerItem + registers.at(e.getIndex()).timeToPay + simClock);
      Event next (EndCheckout, finishCheckout, eve.getCustomer(), e.getIndex());
      events.enqueue (next);
      registers.at(e.getIndex()).Using();
    }
  }
  //incrementWait increases the wait by the correct ammount (see registerqueue for details) and is called each time and event triggers
  //requires: registers is not empty, simclock > lastEvent
  void incrementWait (){
    for (int i = 0; i < (registers.size()); i++){
      registers.at(i).addTime(simClock, lastEvent);
    }
    lastEvent = simClock;
  }
  //totalAverage finds the total average wait of all the customers that went through the stores
  //requires: registers is not empty,
  //returns: a double representing the average waittime of a customer in the store, also couts the individual values that lead to this average
  double totalAverage (){
    int customers = 0;
    double totalTime = 0;
    for (int i = 0; i < registers.size(); i++){
      customers = customers + registers.at(i).CCount();
      totalTime = totalTime + registers.at(i).getWait();
    }
    cout << fixed << totalTime << "     " << customers << endl;
    return totalTime/customers;
  }


};
