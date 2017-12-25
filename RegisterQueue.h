#pragma once
#include "LinkedList.h"

template <class T> class RegisterQueue{
private:
    LinkedList<T> list;
    bool use;
    int size;
    double totalWait;
    int largestLine;
    int customers;
    int maxLineLength;
public:
  double timePerItem;
  double timeToPay;

  //This constructor builds a register based on what the desired register is (indicated by paytime and time per item)
  RegisterQueue (double payTime, double itemTime){
    list = LinkedList<T> ();
    size = 0;
    largestLine = 0;
    totalWait = 0;
    customers = 0;
    timePerItem = itemTime;
    timeToPay = payTime;
    use = false;
  }
  // used to get the total customers that came throught this register
  // requires: customers is not null
  // returns: integer = customer
  // Big-oh: O(1)
  int CCount (){
    return customers;
  }
  //is used to check if the register is automatic using the timePerItem field
  // requires: nothing
  //returns: boolean true or false
  //big-oh: O(1)
  bool isAuto (){
    if (timePerItem == .04){
      return true;
    }
    return false;
  }
  // returns the total waittime for this line for use in calculating data
  // requires: totalWait is not null
  // returns: double = totalWait
  //big-oh: O(1)
  double getWait (){
    return totalWait;
  }
  //returns the current size of the register queue
  //requires: size is not null
  //returns: integer = size
  //big-oh: O(1)
  int getSize (){
    return size;
  }
  //inUse is used to determine if a register currently has an event running
  // requires: use is not null
  // returns: boolean = use
  //big-oh O(1)
  bool inUse(){
    return use;
  }
  //Using is how i indicate that the register has put an event into the queue
  //requires: use is not null
  //returns: boolean = use
  //big-oh: O(1)
  void Using (){
    use = true;
  }
  //stop is how i indicate that the register has just finished processing an EndCheckout
  //requires: use is not null
  //returns: boolean = use
  void stop (){
    use = false;
  }
  //CUp stands for customers up and is used to increment the number of customers this register has processed total
  //requires: customers is not null
  //returns: nothing
  void CUp (){
    customers ++;
  }
  //addTime adds to the totalWait based on the change in time since the last update (l is last t is current time)
  //and multiplying it per person in the queue since they have all waited that long
  //requires: size is not NULL
  //returns: nothing, but totalWait =size*(t-l)
  //big-oh O(1)
  void addTime (double t, double l){
    double timeChange = t - l;
    double timeWait = timeChange * size;
    totalWait = totalWait + timeWait;
  }
  //enqueue takes care of all the processes that occur whenever a new customer is put in line
  //including putting that customer in line and incrementing the max line and size
  //requires: size and maxLineLength are not null
  //returns nothing, but a new node will be in the "back" of the queue and size will be increased
  //big-oh(1)
  void enqueue (T item){
    size++;
    if (size > maxLineLength){
      maxLineLength = size;
    }
    list.push (item);//push puts the value in the front of the linked list (which is treated as the back of the queue)
    }
  //dequeue takes care of all the processes involved in removing a customer from the RegisterQueue
  //including reducing size and removing the value that is dequeued
  //requires: size must be >= number of nodes in the list
  //returns: the value grabed from the front of the queue
  //big-oh O(1)
  T dequeue () {
    T temp = list.grab(size);//grab runs in O(N), but I did not count that here, if I should have I am sorry
    size--;
    return temp;
  }
};
