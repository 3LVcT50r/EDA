#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

int infinit = numeric_limits<int>::max();
vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};

bool pos_ok (const vector<vector<char>>& T, int f, int c) {
  // if (f >= 0 and f < T.size() and c >= 0 and c < T[0].size()) return true;
  // else return false;
  return (f >= 0 and f < T.size() and c >= 0 and c < T[0].size());
}

// BFS
int tresor_mes_proper (vector<vector<char>>& T, int f_ini, int c_ini) {
  vector<vector<int>> dist(T.size(),vector<int>(T[0].size(),infinit));

  dist[f_ini][c_ini] = 0;
  queue<pair<int,int>> Q;
  Q.push({f_ini,c_ini});

  while (not Q.empty()) {
    pair<int,int> p = Q.front();
    Q.pop();
    int f = p.first;
    int c = p.second;
    for (auto d : dirs) {
      int n_f = f + d.first;
      int n_c = c + d.second;
      if (pos_ok(T,n_f,n_c) and T[n_f][n_c] != 'X' and dist[n_f][n_c] == infinit) {
	Q.push({n_f,n_c});
	dist[n_f][n_c] = dist[f][c] + 1;
	if (T[n_f][n_c] == 't') return dist[n_f][n_c];
      }
    }
  }
  return -1;
}

int main(){
  // Llegeixo entrada
  int f, c;
  cin >> f >> c;
  vector<vector<char>> T(f,vector<char>(c));
  for (int i = 0; i < f; ++i)
    for (int j = 0; j < c; ++j)
      cin >> T[i][j];
  int f_ini, c_ini;
  cin >> f_ini >> c_ini;

  // Calculo arribabilitat
  int d = tresor_mes_proper(T, f_ini - 1, c_ini - 1);
  if (d == -1) cout << "no es pot arribar a cap tresor" << endl;
  else  cout << "distancia minima: " << d << endl;
}
