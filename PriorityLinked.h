#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Event.h"
using namespace std;

class PriorityLinked {
private:
  int size;
  struct Node{
    Node* next;
    Event object;
    Node (Event value, Node* next){
      this->next = next;
      this->object = value;
    }
  };
  Node* head;
public:
  PriorityLinked (){
    head = NULL;
    size = 0;
  }
  ~PriorityLinked (){
    if (head){
      Node* lead = head->next;
      Node* follow = head;
      while (lead){
        delete (follow);
        follow = lead;
        lead = lead->next;
      }
      delete (follow);
    }
  }
  //getSize gives the current size of the list
  //requires that size is not NULL
  //returns int = size
  //big-oh O(1)
  int getSize (){
    return size;
  }
  //push puts the given value at the front of the linked list
  //requires nothing
  //returns nothing but does set the new head to be a new node contaitning the given object with a pointer to the old head
  //big-oh O(1)
  void push (Event o){
    head = new Node (o, head);
  }
  //this is one of a few diff void enqueues i am playing around with to see how to get this this working properly
  // void enqueue (Event e){
  //   if (!head){
  //     head = new Node (e, NULL);
  //   } else {
  //     Node * lead = head->next;
  //     Node * follow = head;
  //     if (e.getTime() < head->object.getTime()){
  //       head = new Node (e, head);
  //     } else {
  //       while (e.getTime() >= follow->next->object.getTime() && lead != NULL){
  //         follow = lead;
  //         lead = lead->next;
  //       }
  //       if (lead == NULL){
  //         lead = new Node (e, NULL);
  //       } else {
  //         follow->next = new Node (e, follow->next);
  //       }
  //     }
  //   }
  // }
  //this is the currently best functioning versoin of enqueue and it doesnt even work that well, does what an enqueue does
  //puts a value at the front of the list to be dequeued later
  //requires:more time and effort to be completed
  //returns: nothing but will optimally put the given event in the linked list at the position based on its time
  //big-oh O(N)
  void enqueue (Event e){
    if (!head){ //checks if the head is null and if it is it sets the new node to replace it
      head = new Node (e, NULL);
    } else {
      Node* lead = head; // used to iterate through the list till we reach the desired location
      Node* follow = new Node (e, lead);
      bool done = false; //used with the loop to indicate that a proper location has been found
      int i = 0;
      while (i < size && !done){ //loops through untill either requirement for positioning is found
        if (e.getTime() < lead->object.getTime()){
          follow->next = new Node (e, lead); //replaces the right node by setting the pointer above it to the new node and giving that one a pointer to it
          done = true; //lets the while know we are done here
        }
        follow = lead;//all the necasary increments
        lead = lead->next;
        i++;
      }


//piece of another attempt, i would delete the attempts but they are a helpful reference to see either what worked or what not to do
      // else {
      //   done = true;
      //   while (lead != NULL && !done){
      //     if (e.getTime() < lead->object.getTime()){
      //       done = true;
      //     } else{
      //       lead = lead->next;
      //       follow = follow->next;
      //     }
      //   }
      //   follow->next = new Node (e, lead);
      // }
    }
    size++;//increases size since we just added a node
  }
//pop takes the first value in the list and removes it while returning it
//requires: head is not null
//returns the event stored in head
//big-oh O(1)
  Event pop (){
    Event item = head->object;
    Node* temp = head;
    head = head->next;
    delete (temp);
    size--;
    return item;
  }
};
