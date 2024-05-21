#include <iostream>
#include <vector>
#include <queue>

typedef std::vector< std::vector<char> > Mapa;
typedef std::vector< std::vector<int> > Dist;

struct Pos {
    int x;
    int y;
};

const std::vector<Pos> DIRS = {{1,0}, {0,1}, {-1,0}, {0,-1}};

bool is_valid(Pos &pos, Mapa &map, int n, int m) {
    return pos.x < n and pos.x >= 0 and pos.y < m and pos.y >= 0 and map[pos.x][pos.y] != 'X';
        
}

int bfs(int n, int m, Pos &pos_ini, Mapa &map) {
    std::queue<Pos> q;
    q.push(pos_ini);
    Dist d(n, std::vector<int> (m,-1));

    d[pos_ini.x][pos_ini.y] = 0;

    while (not q.empty()) {
        Pos pos = q.front();
        q.pop();

        if (map[pos.x][pos.y] == 't') return d[pos.x][pos.y];

        else {
            for (auto p : DIRS) {
                Pos new_pos = {pos.x + p.x, pos.y + p.y};
                if (is_valid(new_pos, map, n, m) and d[new_pos.x][new_pos.y] == -1) {
                    q.push(new_pos);
                    d[new_pos.x][new_pos.y] = d[pos.x][pos.y] + 1;
                }
            }
        }
    }
    return -1;
}

int main() {

    int n, m;
    std::cin >> n >> m;

    Mapa map(n, std::vector<char>(m));
    

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> map[i][j];
        }
    }

    Pos pos_ini;
    std::cin >> pos_ini.x >> pos_ini.y;

    --pos_ini.x;
    --pos_ini.y;

    int dist = bfs(n, m, pos_ini, map);
    if (dist == -1) {
        std::cout << "no es pot arribar a cap tresor" << std::endl;
    }
    else {
        std::cout << "distancia minima: " << dist << std::endl;
    }
}