#pragma once
#include "LinkedList.h"
//#include "Iterator.h"
#include "Event.h"
using namespace std;

class MyPriorityQueue{
private:
  LinkedList<Event> list;
  int size;

public:
  MyPriorityQueue (){
    list = LinkedList<Event> ();
    size = 0;
  }
  //
  void enqueue (Event e){
    if (!list.head){
      list.makeNode(e, NULL);
      list.makeAnew(list.head);
    } else{
      findSpot(e);
      setNode(e);
    }
    size++;
    list.listCheck();
  }
  void setNode (Event e){
    list.makeNode(e, list.target);
    list.tail->next = list.handMadeNode;
  }
  void findSpot(Event e){
    list.iterReset();
    list.target = list.head->next;
    list.tail = list.head;
    bool found;
    if (e.getTime() < list.head->object.getTime()){
      found = true;
    } else {
      found = false;
    }
    while (list.target != NULL && !found){
      if (e.getTime() < list.target->object.getTime()){
        found = true;
      } else {
        list.tail = list.target;
        list.target = list.target->next;
      }
    }

  }
  int getSize (){
    return size;
  }
  Event dequeue (){
    size--;
    Event item = list.pop();
    return item;
  }
};
