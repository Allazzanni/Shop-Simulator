#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


template <class T> class LinkedList{
private:
  struct Node{
    Node* next;
    T object;
    Node (){
      this->next = NULL;
    }
    Node (T value, Node* next){
      this->next = next;
      this->object = value;
    }
  };

public:
  Node* target;
  Node* tail;
  Node* head;
  Node* handMadeNode;
  LinkedList (){
    head = NULL;
  }
  ~LinkedList (){
    if (head){
      Node* lead = head->next;
      Node* follow = head;
      while (lead){
        delete (follow);
        follow = lead;
        lead = lead->next;
      }
      delete (follow);
      delete (handMadeNode);
      delete (target);
      delete (tail);
    }
  }
  //makeAnew takes a node and replaces it with the new last node made by the makeNode method, it was the easiest way to
  void makeAnew(Node* node){
    Node* temp = node;
    node = handMadeNode;     //MAY NOT NEED
    delete(temp);
  }
  //next works as the next method for a kind of built in iterator with the fields target and tail which serve as the current and last
  //requires: target is not NULL
  // returns: the next node in the linked list, also changes target to be on that node and follow to be the node above it
  //big-oh O(1)
  Node* next (){
    if (!hasNext()) throw (2);
    tail = target;
    target = target->next;
    return target;
  }
  //returns last
  Node* last (){   //MAY NOT NEED
    return tail;
  }
  //resets the target and tail fields to be where they are needed for iterateing down the queue (used where you might declare an iterator)
  //Requires: head is not null
  //returns: nothing, but target is now the child of head and follow is head
  //big-oh O(1)
  void iterReset (){
    target = head->next;
    tail = head;
  }
  //getObject returns the stored object
  //requires: nothing
  //returns: the object that is stored in the Node
  //big-oh O(1)
  T getObject (){
    return target->object;
  }
  //makeNode makes a node and stores it in the handMadeNode field to be used by any method that might need it
  //node was not allowed to be made outside of in this class, so this was a good way to make a node for other classes methods
  //requires: nothing, but be careful with the pointers
  //big-oh O(1)
  void makeNode (T o, Node* next){
      Node newNode (o, next);
      handMadeNode = &newNode;
  }
  //hasNext is the hasNext function for the kind of built in iterator that is used to check the node stored in target->next
  //requires: nothing
  //returns: boolean true or false
  //big-oh O(1)
  bool hasNext (){
    if (target->next){
      return true;
    }
    return false;
  }
  //push puts an object into a node and then puts that node at the top of the linked list
  //requires nothing
  //returns nothings, but the current head will now be the next in the new head
  //big-oh O(1)
  void push (T o){
    head = new Node (o, head);
  }
  //pop takes the object stored in head out of the list and returns it
  //requires: head is not null
  //returns: the object stored in head
  //big-oh O(1)
  T pop (){
    T item = head->object;
    Node* temp = head;
    head = head->next;
    delete (temp);
    return item;
  }
  //grab is a modified version of get that also removes the value to save memory
  //requires: head should not be null, but it has an error check and the index needs to be equal to or less than the
  //acutal size of the list. this one was written with registerqueue in mind and may not work for just fetching a value in the middle
  //returns: the value stored at the index given, also that node has ben removed
  //big-oh O(N), where N is based on the index given
  T grab (int index){
    if (!head) throw(1);
    int i = 0;
    Node* next = head;
    while (i < index -1){
      i = i + 1;
      if (next->next){
        next = next->next;
      } else {
        throw (1);
      }
    }
    T object = next->object;
    delete(next);
    return object;
  }
  //get finds the object at the given index and returns it without removing it
  //requires that the index given is less than the actual length of the LinkedList
  //returns the value at the index
  //big-oh O(N), where N is the index given
  T get (int index){
    if (!head) throw(1);
    int i = 0;
    Node* next = head;
    while (i < index -1){
      i = i + 1;
      if (next->next){
        next = next->next;
      } else {
        throw (1);
      }
    }
    return next->object;
  }
  //sets the ostream to work for linked list, do not think I ever used, but it is here
  friend ostream& operator << (ostream& os, const LinkedList& list){
    Node* next = list.head;
    while (next != NULL){
      os << next->object << " ";
      next->next;
    }
    return os;
  }
















};
