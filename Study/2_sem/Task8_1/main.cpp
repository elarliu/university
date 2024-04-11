#include<iostream>
#include "ArrayList.cpp"
#include "LinkedList.cpp"
// #include "ArrayList.cpp"
using namespace std;

int main() {
  Collection * c = new ArrayList<int>();
  int * a0 = new int;
  *a0 = 5;
  int * a1 = new int;
  *a1 = 4;
  int * a2 = new int;
  *a2 = 3;
  c->add(a0);
  c->add(a1);
  ArrayList<int> * arr = dynamic_cast<ArrayList<int> *>(c);
  arr->add(a2);
  cout<<c->contains(a0)<<endl;
  cout<<arr->contains(a1)<<endl;
  delete c;
  // return EXIT_SUCCESS;
  c = new LinkedList<char>();
  char * c1 = new char;
  *c1 = 'f';
  c->add(c1);
  delete c1;
  c1 = new char;
  *c1 = 'g';
  c->add(c1);
  LinkedList<char> * ll = dynamic_cast<LinkedList<char> *>(c);
  char * c2 = new char;
  *c2 = 'h';
  ll->add(c2);
  cout<<c->contains(c2)<<endl;
  // cout<<*((char *)ll->remove(c2))<<endl;
  delete c;
  delete c1;
  delete c2;
  return EXIT_SUCCESS;
};
