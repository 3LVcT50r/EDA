#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  string name;
  map<string, int> casino;

  while (cin >> name) {
    string op;
    cin >> op;

    map<string,int>::iterator it = casino.find(name);

    if (op == "enters") {
      if (it != casino.end()) cout << name << " is already in the casino" << endl;
      else casino[name] = 0;
    }

    else if (op == "wins") {
      int val;
      cin >> val;
      
      if (it == casino.end()) cout << name << " is not in the casino" << endl;
      else it->second += val;
    }
    else { //leaves
      if (it == casino.end()) cout << name << " is not in the casino" << endl;
      else {
        //map<string,int>::iterator it = casino.find(name);
        cout << name << " has won " << it->second << endl;
        casino.erase(it);
      }
    }
  }

  cout << "----------" << endl;
  for (map<string,int>::iterator it = casino.begin(); it != casino.end(); ++it) {
    cout << it->first << " is winning " << it->second << endl;
  }

}