#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef vector<char> Col;
typedef vector<Col> Board;
typedef pair<int, int> Pos;
typedef vector<Pos> Positions;

struct Info {
    //int distance = -1;
    pair<int,int> pr;
    vector<pair<int,int>> vect;
};

void wv(vector<pair<int,int>> &v) {
    int size = v.size();
    for (int i = 0; i < size; ++i) {
        cout << '[' << v[i].first+1 << ',' << v[i].second+1 << ']';
    }
    cout << endl;
}


Positions adjacents(Pos p) {
  Positions pos;
  pos.push_back({p.first+1, p.second});    // Down
  pos.push_back({p.first, p.second+1});    // Right
  pos.push_back({p.first-1, p.second});    // Up
  pos.push_back({p.first, p.second-1});    // Left
  return pos;
}

bool pos_ok(Pos p, const Board& board) {
  // Check that not overflows the board margins and is not a obstacle on the board
  if (0 <= p.first and p.first < board.size()
      and 0 <= p.second and p.second < board[0].size()
      and board[p.first][p.second] != 'X') return true;
  else return false;
}

vector<Pos> camino(map<Pos,Pos> vst, Pos ini, Pos act) {
    vector<Pos> camino;
    //cout << "HOLA1" << endl;
    camino.push_back(act);
    while ((act.first != ini.first) or (act.second != ini.second)) {
        //cout << "HOLA" << endl;
        Positions adjacent = adjacents(act);
        for (auto pos : adjacent) {
            /*
            if ((pos.first < n and pos.second < m and pos.first > -1 and pos.second > -1) and dist[pos.first][pos.second] != -1 and dist[pos.first][pos.second] < dist[act.first][act.second]) {
                act = pos;
                camino.push_back(pos);
                break;
            }
            */
            //map<Pos,Pos>::const_iterator it = vst.find(pos);
            if (vst[act] == pos) {
                act = pos;
                camino.push_back(pos);
                break;
            }
        }
    }
    return camino;
}
bool bool_map(map<Pos,Pos> vst, Pos p) {
    map<Pos,Pos>::const_iterator it = vst.find(p);
    if (it != vst.end()) return true;
    else return false;
}

Info BFS(Pos src, const Board& board) {
  // Indicates if some position has been visited
  //vector<vector<int> > dist(board.size(), vector<int>(board[0].size(), -1));
  //dist[src.first][src.second] = 0;  // Set the source position as visited
  map<Pos,Pos> vst;
  queue<Pos> q;
  q.push(src);    // Add the source position to queue

  //int distance = -1;

  Info inf;

  while (not q.empty()) {
    Pos p = q.front();
    q.pop();

    // If a treasure has been found, it return true
    if (board[p.first][p.second] == 't') {
        //Info inf;
        //inf.distance = dist[p.first][p.second];
        inf.pr.first = p.first;
        inf.pr.second = p.second;
        inf.vect = camino(vst, src, p); 
        return inf;
    }

    // For all adjacent positions (Down, Right, Up, Left)
    Positions adjacent = adjacents(p);
    for (auto pos : adjacent) {
      // Checks if it's a position on the board and hasn't been visited
      if (pos_ok(pos, board) and not(bool_map(vst,pos))) {
        //dist[pos.first][pos.second] = dist[p.first][p.second] + 1;
        vst.insert(make_pair(pos,p));
        q.push(pos);
      }
    }
  }

  return inf;    // There isn't a path
}

int main() {
  int n, m;
  cin >> n >> m;

  // Read board
  Board board(n, Col(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> board[i][j];

  // Get initial pos
  int r, c;
  cin >> r >> c;

  Info imf = BFS(Pos({r-1, c-1}), board);
  //if (res == -1) cout << "no treasure can be reached" << endl;
  cout << imf.pr.first+1 << ' ' << imf.pr.second+1 << endl;
  wv(imf.vect);
}