#include <iostream>
#include <vector>
using namespace std;
typedef vector< vector<int> > Graf;

void print(const vector<int> &top) {
    for (int i = 0; i < top.size(); ++i) {
        if (i < top.size()-1) cout << top[i] << ' ';
        else cout << top[i];
    }
    cout << endl;
}
/*
bool se_puede(const Graf &g, const vector<int> &top, int y) {
    vector<int> x = g[y];
    if (x.size() == 0) return true;
    else {
        int cond = 0;
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < top.size(); ++j) {
                if (x[i] == top[j]) ++cond;
            }
        }
        return (cond == x.size());
    }
}

bool puesto(const vector<int> &top, int i) {
    for (int j = 0; j < top.size(); ++j) {
        if (top[j] == i) return false;
    }
    return true;
}
*/
void topo(const Graf &g, vector<int> &ge, vector<int> &top) {
    if (g.size() == top.size()) print(top);
    else {
        for (int i = 0; i < g.size(); ++i) {
            if (ge[i] == 0) {
                top.push_back(i);
                --ge[i];
                for (int j = 0; j < g[i].size(); ++j) --ge[g[i][j]];
                topo(g, ge, top);
                for (int j = 0; j < g[i].size(); ++j) ++ge[g[i][j]];
                ++ge[i];
                top.pop_back();
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int x, y;
    Graf g(n); 
    vector<int> ge(n, 0);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        g[x].push_back(y);
        ++ge[y];
    }
    vector<int> top;
    topo(g, ge, top);
}