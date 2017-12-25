
#include "Customer.h"
#include "Event.h"
#include "RegisterQueue.h"
#include "PriorityQueue.h"
#include "PriorityLinked.h"
using namespace std;


//int testPriority ();
//int testRegisters ();

//int main(){
  //cout << "running main";
  //testPriority ();
  //return 0;
//}
int main (){
  cout << "here" << endl;
  PriorityLinked p;
  double i = 1;
  int j = 1;
  double k = 1;
  Customer cust (i, j, k);
  Event e (Arrival, 53.4, cust);
  cout << "here2" << endl;
  p.enqueue (e);
  cout << "here3" << endl;
  i= i + 1;
  j++;
  k = k + 1;
  cust = Customer (i, j, k);
  e = Event (Arrival, 53.3, cust);
  p.enqueue (e);
  i= i + 1;
  j++;
  k = k + 1;
  i= i + 1;
  j++;
  k = k + 1;
  cust = Customer (i, j, k);
  e = Event (Arrival, 54.3, cust);
  p.enqueue (e);
  i= i + 1;
  j++;
  k = k + 1;
  cout << "dstart" << endl;
  cout << p.pop().getCustomer() << endl;
  cout << "dend" << endl;
  cout << "dstart" << 2 << endl;
  cout << p.pop().getCustomer() << endl;
  cout << "dend" << 2 << endl;
  cout << "dstart3" << endl;
  cout << p.pop().getCustomer() << endl;
  cout << "dend3" << endl;
  return 0;
}
int whatever(){
  RegisterQueue<int> r (1.5, .01);
  r.enqueue (1);
  cout << "1" << endl;
  return 0;
  MyPriorityQueue p;
  double i = 1;
  int j = 1;
  double k = 1;
  Customer cust (i, j, k);
  Event e (Arrival, 57.3, cust);
  p.enqueue (e);
  i= i + 1;
  j++;
  k = k + 1;
  cust = Customer (i, j, k);
  e = Event (Arrival, 57.3, cust);
  p.enqueue (e);
  i= i + 1;
  j++;
  k = k + 1;
  i= i + 1;
  j++;
  k = k + 1;
  cust = Customer (i, j, k);
  e = Event (Arrival, 57.3, cust);
  p.enqueue (e);
  i= i + 1;
  j++;
  k = k + 1;
  cout << p.dequeue().getCustomer() << endl;
  cout << p.dequeue().getCustomer() << endl;
  cout << p.dequeue().getCustomer() << endl;
  return 0;
}
