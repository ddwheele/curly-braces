#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int x = 10;
  int y = 20;  
  int& ref = x;

  cout <<"int x = 10;  int y = 20; int& ref = x;" << endl;
  cout << "\tx = " << x << ", ref = " << ref << ", y = " << y << endl;
  ref = y;
  cout << "ref = y" << endl;
  cout << "\tx = " << x << ", ref = " << ref << ", y = " << y << endl;
  
  cout << "y = 3" << endl;
  y = 3;
  cout << "\tx = " << x << ", ref = " << ref << ", y = " << y << endl;
  cout <<"\n---------------"<< endl;

  int* ptr = new int(5);
  int*& refptr = ptr;
  cout << "int a = new int(5); int& refa = a;" << endl;
  cout << "\tptr = " << ptr << ", refptr = " << refptr  << endl;
  cout << "\t*ptr = " << *ptr << ", *refptr = " << *refptr  << endl;

  *ptr += 10;
  cout << "*ptr += 10;" << endl;
  cout << "\tptr = " << ptr << ", refptr = " << refptr  << endl;
  cout << "\t*ptr = " << *ptr << ", *refptr = " << *refptr  << endl;

  *refptr += 23;
  cout << "*refptr += 23;" << endl;
  cout << "\tptr = " << ptr << ", refptr = " << refptr  << endl;
  cout << "\t*ptr = " << *ptr << ", *refptr = " << *refptr  << endl;

  delete ptr;

  cout << "delete ptr;" << endl;
  cout << "\tptr = " << ptr << ", refptr = " << refptr  << endl;
  cout << "\t*ptr = " << *ptr << ", *refptr = " << *refptr  << endl;

  return 0;
}
