#include "Player.hh"
#include <queue>
#include <vector>
#include <map>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME VInge


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  const vector<Dir> dirs = {Up,Down,Left,Right};

  struct InfoFood{
    //int distFood = -1;
    //Pos PosFood;
    vector<Pos> distMFood;
    bool foodi = false;

    vector<Pos> distMZomb;
    bool zombiei = false;

    vector<Pos> distMPlayer;
    bool playeri = false;
  };

  //Retorna si el jugador puede moverse hacia esa direccion o no
  bool pos_oki(Pos p) {
    return (pos_ok(p) and cell(p).type != Waste and not(cell(p).id != -1 and unit(cell(p).id).type == Dead)/*and cell(p).id != me()*/);
  }

  //NO HACE FALTA PUSH_BACK -> CAMBIAR SI ES MUY INEFICIENTE (HACERLO CON UN VECTOR DE TAMAÃ‘O "DISTANCIA"+1)
  vector<Pos> camino(vector<vector<int>> &dist, Pos ini, Pos act) {
    vector<Pos> camino;
    camino.push_back(act);
    while((act.i != ini.i) or (act.j != ini.j)) {
      cerr << "Bucle camino" << endl;
      for (auto d : dirs) {
        Pos new_pos = act + d;
        cerr << "Si" << endl;
        if (pos_oki(new_pos) and dist[new_pos.i][new_pos.j] != -1 and dist[new_pos.i][new_pos.j] < dist[act.i][act.j]) {
          act = new_pos;
          cerr << new_pos.i << ' ' << new_pos.j << endl;
          camino.push_back(new_pos);
          break;
        }
      }
    }
    cerr << "Acabau" << endl;
    return camino;
  }

  InfoFood bfs_food(const Pos pos_ini) {
    InfoFood ifm;
    vector<vector<int>> visit(60, vector<int>(60, -1));
    map<Pos,Pos> vst;
    visit[pos_ini.i][pos_ini.j] = 0;
    //vst.insert(make_pair())
    queue<Pos> q;
    q.push(pos_ini);

    //double st = status(me());
    while(not q.empty()) {
      //cerr << "Bucle" << endl;
      Pos p = q.front();
      q.pop();

      if (cell(p).food) {
        cerr << "Comida" << endl;
        //ifm.food = true;
        //ifm.PosFood = p;
        //ifm.distFood = visit[p.i][p.j];
        ifm.foodi = true;
        cerr << "Antes" << endl;
        ifm.distMFood = camino(visit, pos_ini, p);
        cerr << "camino" << endl;
        return ifm;
      }
      
      else if (cell(p).id != -1) {
        if (unit(cell(p).id).type == Zombie) {
          cerr << "Zombie" << endl;
          ifm.zombiei = true;
          cerr << "Antes" << endl;
          ifm.distMZomb = camino(visit, pos_ini, p);
          cerr << "No" << endl;
          return ifm;
        } 
        else if (unit(cell(p).id).type == Alive and unit(cell(p).id).player != me()/* and strength(unit(cell(p).id).player) < strength(me())*/) {
          cerr << "Jugador" << endl;
          ifm.playeri = true;
          ifm.distMPlayer = camino(visit, pos_ini, p);
          return ifm;
        }
        
      }
      
      for (auto d : dirs) {
        Pos new_pos = p + d;
        if (pos_oki(new_pos) and visit[new_pos.i][new_pos.j] == -1) {
          visit[new_pos.i][new_pos.j] = visit[p.i][p.j] + 1;
          q.push(new_pos);
        }
      }
      //st = status(me());
    }

    return ifm;
  }

  Dir direcc(Pos ini, Pos fin) {
    Pos ac;
    ac.i = fin.i-ini.i;
    ac.j = fin.j-ini.j;
    if (ac.i == 1 and ac.j == 0) return Down;
    else if (ac.i == -1 and ac.j == 0) return Up;
    else if (ac.i == 0 and ac.j == 1) return Right;
    else return Left;
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //Unidades vivas
    vector<int> alive = alive_units(me());

    for (auto id : alive) {
      
      for (auto d : dirs) {
        Pos new_pos = unit(id).pos + d;
        
        if (cell(new_pos).id != -1) {
          if (unit(cell(new_pos).id).type == Zombie or (unit(cell(new_pos).id).type == Alive and unit(cell(new_pos).id).player != me() and strength(unit(cell(new_pos).id).player < strength(me())))) {
            move(id, d);
          } 
          else if (unit(cell(new_pos).id).type == Alive and unit(cell(new_pos).id).player != me() and strength(unit(cell(new_pos).id).player < strength(me()))) {
            move(id, d);
          }
        }
      }
      
      //DODGE
      Pos DR, DL, UR, UL;
      DR.i = unit(id).pos.i+1;
      DR.j = unit(id).pos.j+1;

      DL.i = unit(id).pos.i+1;
      DL.j = unit(id).pos.j-1;

      UR.i = unit(id).pos.i-1;
      UR.j = unit(id).pos.j+1;

      UL.i = unit(id).pos.i-1;
      UL.j = unit(id).pos.j-1;
      
      if (cell(DR).id != -1 or cell(DL).id != -1 or cell(UL).id != -1 or cell(UR).id != -1) {
        if (pos_oki(unit(id).pos+Up) and unit(cell(DR).id).type == Zombie) move(id, Up);
        else if (pos_oki(unit(id).pos+Up) and unit(cell(DL).id).type == Zombie) move(id, Up);
        else if (pos_oki(unit(id).pos+Down) and unit(cell(UR).id).type == Zombie) move(id, Down);
        else if (pos_oki(unit(id).pos+Down) and unit(cell(UL).id).type == Zombie) move(id, Down);
      }
      
      InfoFood ifm = bfs_food(unit(id).pos);
      Pos posi;
      if (ifm.foodi) posi = ifm.distMFood[ifm.distMFood.size()-2];
      else if (ifm.zombiei) posi = ifm.distMZomb[ifm.distMZomb.size()-2];
      else if (ifm.playeri) posi = ifm.distMPlayer[ifm.distMPlayer.size()-2];
      Dir d = direcc(unit(id).pos, posi);
      move(id, d);
    }

  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);