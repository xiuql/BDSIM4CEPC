#include <iostream>
#include <list>

using namespace std;

class A {

public:

  int val;
  int foo() { return 0;}
};

struct B {
  int val;
  double dval;
  char *name;
};

int main()
{
  list<double> *a = new list<double>;

  cout<<"double  -> "<<sizeof(double)<<endl;
  cout<<"double* -> "<<sizeof(double*)<<endl;
  cout<<"list*   -> "<<sizeof(a)<<endl;
  cout<<"A*      -> "<<sizeof(A*)<<endl;
  cout<<"B*      -> "<<sizeof(struct B*)<<endl;

}
