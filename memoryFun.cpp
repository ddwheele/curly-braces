#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>

using namespace std;

// clang++ -std=c++20 memoryFun.cpp -o memFun

class Solution {
public:
    int lastStoneWeightII( vector<int>& stones) {
        //sort(stones.begin(), stones.end());
        if(stones.size() == 2) {
            return abs(stones[0] - stones[1]);
        }
        int total = accumulate(stones.begin(), stones.end(), 0);
        int cutoff = total/2;
        
        set<int> lastRow;
        lastRow.insert(stones[0]);
        lastRow.insert(-stones[0]);

        for(int i=1; i<stones.size(); i++) {
            set<int> row;
            for(auto it = lastRow.begin(); it != lastRow.end(); ++it) {
                int sum = *it;
                int plus = sum + stones[i];
                int minus = sum - stones[i];
            //    if(plus < cutoff) {
                    row.insert(plus);
              //  }
            //    if(minus > -cutoff) {
                    row.insert(minus);
             //   }
            }
            lastRow = row;
        }
        for(int i : lastRow) {
            cout << i << " ";
        }
        cout << endl;
        for(int i : lastRow) {
           
            if(i>=0) {
                cout << "Answer: " << i << endl;
                return i;
            }
        }
        return numeric_limits<int>::max();
    }
};

void runATest( vector<int>&& stones, int expected) {
  cout << "===== Running test {" ;
   for(int s : stones) {
    cout << s << ", ";
  }
  cout << "}" << endl;
  Solution s;
  int got = s.lastStoneWeightII(stones);
  cout <<"For stones {";
  for(int s : stones) {
    cout << s << ", ";
  }
  cout << "}, got " << got << ", expected " << expected << endl;
  return;
}

int main() {
  runATest({2, 1}, 1);
  runATest({31,26,33,21,40}, 5);
  runATest({2,7,4,1,8,1}, 1);
  runATest({2,1,6,4,5}, 0);
  return 0;
}

void memfun() {
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
}