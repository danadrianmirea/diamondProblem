#include <bits/stdc++.h>

using namespace std;

class A
{
  public:
    int a;
    A() : a(0) { cout << "Test ct A" << endl; }
    ~A() { cout << "Test dt A" << endl; }
    void printInt() { cout << a << endl; }
};


class B : public A // all can be solved by using virtual inheritance, meaning to use virtual public A here and in C's definition
{
  public:
    B() { cout << "Test ct B" << endl; }
    ~B() { cout << "Test dt B" << endl; }
   void func() { cout << "B func" << endl; }
};

class C : public A
{
  public:
    C() { cout << "Test ct C" << endl; }
    ~C() { cout << "Test dt C" << endl; }
   void func() { cout << "C func" << endl; }
};

class D: public B, public C
//class D: public B
{
  public:
    D() { cout << "Test ct D" << endl; }
    ~D() { cout << "Test dt D" << endl; }
};

int main()
{
  D d;
  //d.func(); gives an "request for member 'func' is ambiguous error
  //d.printInt(); // request for member printInt is ambiguous; either accessing conflicting members from B and C, or members from A gives same result but for different reasons. In the first one we have func defined in both parents B and C. In the second case, we have two instances of the same grandparent so the compiler doesn't know which one's data we are trying to refer to.

  d.B::func();
  d.C::func();
 // d.C::func(); // important: if the D inheritance is not class D: public B, public C and is just class D: public B, C as some would be tempted to type, C is inherited as private and we get an "C is an innacesible base of D error, totally unrelated to diamond inheritance, but only to multiple inheritance syntax

  //d.B::A::a = 8; // this is valid only with virtual inheritance, otherwise gives an 'A' is an ambiguous base of 'D' error because there are two instances of A in D. This type of calling does not solve the problem

  // the way to acces B::A and C::A data is through pointers to the two copies of A inside D by casting to a B* and C* respectively to solve the ambiguity
  B* d_as_b = (B*)(&d);
  d_as_b->a = 8;
  d_as_b->printInt();
  //d.printInt(); // request for member 'printInt' is ambiguous
  d.B::printInt();
  C* d_as_c = (C*)&d;
  d_as_c->a = 9;
  d_as_c->printInt();
  d.C::printInt();

  return 0;
}
