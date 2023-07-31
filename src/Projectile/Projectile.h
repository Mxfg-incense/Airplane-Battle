#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObjects.h"
//projectile 
class projectile :public GameObject {
  public:
    projectile(int, int,int, int, int, double, GameWorld *,int);
    virtual bool isprojectile() override;
    virtual void Minus_hp(int) override;
    virtual int Get_atk() const override;
    virtual bool isenemy() override;

  private:
    int atk;
};
//player_projectile 

class blue :public projectile {
  public :
    blue(int up,int ,int,GameWorld*);
    virtual void Update() override;
    virtual bool isenemy() override;
};



//enemy_projectile 

class red :public projectile {
  public :
    red(int x,int y,int dir,int atk,GameWorld* w);
    virtual void Update() override;
    virtual bool isenemy() override;
};

class Meteor_flying :public projectile {
  public :
    Meteor_flying(int x, int y,GameWorld*);
    virtual bool ismeteor() override;
    virtual bool isenemy() override;
    virtual void Update() override;
};
#endif