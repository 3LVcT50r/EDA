#include <iostream>
#include <queue>

using namespace std;

int main() {

  char op;
  priority_queue<int> q;
  int x;

  while (cin >> op) {
    if (op == 'A') {

      if (q.empty()) cout << "error!" << endl;
      else {
        cout << q.top() << endl;
      }
    } 
    else if (op == 'S') {

      //int x;
      cin >> x;
      q.push(x); 
    }
    else if (op == 'I') {

      if (q.empty()) cout << "error!" << endl;
      else {
        //int x;
        cin >> x;
        q.push(q.top() + x);
        q.pop();
      }
    }
    else if (op == 'R') {
      q.pop();
    } 
    else if (op == 'D') {

    if (q.empty()) cout << "error!" << endl;
    else {
      //int x;
      cin >> x;
      q.push(q.top() - x);
      q.pop();
      }
    }
  }
}