#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.h"

class GameWorld;
//enenmy
class Enemy: public Ship {
  public:
    Enemy(int imageID,GameWorld *w,int,int,int,int,int);
    virtual bool isenemy() override;
    virtual void Update() override;
    virtual void after_die() override;
    virtual int Get_atk() const override;
    virtual void lauch_projectile();
    virtual void sprint();
    virtual void die_drop();
    void getStrategy();
    void applyStrategy();
    void setspeed(int);
    void setMovedir(int);
    void setstratagy(int);

  private:
    int atk, speed, bonus,stratagy=0,stratagy_kind=0;
};
//Alpha
class Alpha: public Enemy {
  public:
    Alpha(GameWorld *);
    virtual void lauch_projectile() override;
};

//Sigama
class Sigma: public Enemy {
  public:
    Sigma(GameWorld *);
    virtual void sprint() override;
    virtual void die_drop() override;
};

//omega
class Omega: public Enemy {
  public:
    Omega(GameWorld *);
    virtual void lauch_projectile() override;
    virtual void die_drop() override;
};
#endif