#ifndef SHIP_H
#define SHIP_H

#include "GameObjects.h"

class GameWorld;
//ship
class Ship : public GameObject {
  public :
    Ship(int imageID, int x, int y, int direction,int,int,GameWorld* w);
    virtual bool isprojectile() override;
    virtual void after_die();
    void Minus_hp(int) override;
    int Get_energy() const;
    virtual int Get_hp() const override;
    void Set_hp(int);
    void Minus_energy(int);
  private :
    int hp,energy;
};

//player
class Player : public Ship {
  public:
    Player(GameWorld*);
    virtual void Update() override;
    int Get_up() const;
    int Get_meteor();
    void add_hp(int);
    void add_up(int);
    void add_meteor(int);
    virtual bool isenemy() override;
  private:
    int up=0,meteor=0;
    
};
#endif