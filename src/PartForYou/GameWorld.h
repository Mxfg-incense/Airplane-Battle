#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"

class GameObject;

class Player;

class Enemy;

class projectile;

class Goodie;

class Meteor_flying;

class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  void Minus_onscreen();

  void append_goodie(GameObject *);

  void append_star(GameObject*);

  void append_explosion(GameObject*);

  void append_projectile(GameObject*);

  void append_enemy(GameObject*);

  std::list<GameObject *>::iterator Get_Begin();

  std::list<GameObject *>::iterator Get_End();

  void attack_blue(GameObject*);

  void Collision_Handling(Enemy*,int);

  bool Goodie_player(Goodie*);

  void Increase_hp(int);

  void Increase_up(int);

  void Increase_meteor(int);

  void red_player(projectile*);

  void meteor_enemy(Meteor_flying *);

  void player_enemy(Player *);

  int Get_playerX();

  int Get_playerY();

  void add_destroyed();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

private:
  std::list<GameObject *> gameobjects;
  Player* player=nullptr;
  int maxOnscreen,destroyed,live,required,onscreen,p1,p2,p3,p;
};

bool Check_collision(const GameObject *lhs, const GameObject *rhs);
#endif // !GAMEWORLD_H__